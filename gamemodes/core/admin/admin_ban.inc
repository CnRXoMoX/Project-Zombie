#include <YSI_Coding\y_hooks>

static
    Statement: stmt_checkBan,
    Statement: stmt_getUID
;

hook OnMySQLConnected()
{
    static const checkQuery[] = "\
    SELECT \
        *, DATE_FORMAT(ban_date, '"SQL_DATETIME_FORMAT"') AS date_ban, \
        DATE_FORMAT(unban_date, '"SQL_DATETIME_FORMAT"') AS date_unban, \
        TIMESTAMPDIFF(SECOND, CURRENT_TIMESTAMP(), unban_date) AS expired \
    FROM \
        bans \
    WHERE \
        username = ? OR gcpi = ? OR ip = ? LIMIT 1 \
    ";
    stmt_checkBan = MySQL_PrepareStatement(MySQL_GetHandle(), checkQuery);

    static checkuidQuery[] = "\
    SELECT \
        username \
    FROM \
        players \
    WHERE \
        username = ? \
    ";
    stmt_getUID = MySQL_PrepareStatement(MySQL_GetHandle(), checkuidQuery);
    return 1;
} 

hook OnPlayerConnect(playerid)
{
    Ban_CheckUser(playerid);
    return 1;
}

Ban_AddUser(playerid, byid = INVALID_PLAYER_ID, reason[], interval_type, banduration) {
    new
        playerIP[16 + 1],
        bannerName[MAX_PLAYER_NAME],
        string[512],
        playerGCPI[60],
        playerName[MAX_PLAYER_NAME]
    ;

    GetPlayerName(playerid, playerName, sizeof(playerName));
    GetPlayerIp(playerid, playerIP, sizeof(playerIP));
    gpci(playerid, playerGCPI, sizeof(playerGCPI));

    strcpy(bannerName, (byid == INVALID_PLAYER_ID ? "SERVER" : playerName) , MAX_PLAYER_NAME);

    new
        interval[6]
    ;
    switch(interval_type) {
        case 0: strcpy(interval, "DAY", sizeof(interval));
        case 1: strcpy(interval, "MONTH", sizeof(interval));
        case 2: strcpy(interval, "YEAR", sizeof(interval));
    }

    static const query[] = "\
        INSERT INTO bans \
            (username, ip, gcpi, reason, admin, ban_date, unban_date) \
        VALUES \
            ('%e', '%e', '%e', '%e', '%e',  CURRENT_TIMESTAMP(), DATE_ADD(CURRENT_TIMESTAMP(), INTERVAL %i %s))"
    ;
    mysql_format(MySQL_GetHandle(), string, sizeof(string), query, playerName, playerIP, playerGCPI, reason, bannerName, banduration, interval);

    Logger_Dbg(ADMIN_DEBUG_HANDLER, "admin has banned", Logger_P(playerid), Logger_P(byid));
    return mysql_tquery(MySQL_GetHandle(), string);
}

void:OffBan_AddUser(const username[], byid = INVALID_PLAYER_ID, reason[], interval_type, banduration)
{
    new 
        banusername[MAX_PLAYER_NAME],
        string[512],
        bannerName[MAX_PLAYER_NAME],
        banreason[MAX_BAN_REASON];
    strcpy(banusername, username, sizeof(banusername));
    GetPlayerName(byid, bannerName, MAX_PLAYER_NAME);
    
    inline OnPlayerOffBan() {
        new
            playerNAME[MAX_PLAYER_NAME];

        MySQL_BindResult(stmt_getUID, 0, playerNAME);

        if(MySQL_Statement_FetchRow(stmt_getUID)) {

            new
                interval[6]
            ;
            switch(interval_type) {
                case 0: strcpy(interval, "DAY", sizeof(interval));
                case 1: strcpy(interval, "MONTH", sizeof(interval));
                case 2: strcpy(interval, "YEAR", sizeof(interval));
            }

            static const query[] = "\
            INSERT INTO bans \
                (username, ip, gcpi, reason, admin, ban_date, unban_date) \
            VALUES \
                ('%e', '%e', '%e', '%e', '%e',  CURRENT_TIMESTAMP(), DATE_ADD(CURRENT_TIMESTAMP(), INTERVAL %i %s))"
            ;
            mysql_format(MySQL_GetHandle(), string, sizeof(string), query, playerNAME, 0, 0, reason, bannerName, banduration, interval);
            mysql_tquery(MySQL_GetHandle(), string);
            SendMsgAllF(COLOR_MODERATION, "**[OFFLINE ACCOUNT DISABLED]: %s has been banned for %s", playerNAME, banreason);
        }
        else {
            if(byid != INVALID_PLAYER_ID) {
                return SendErrorMsgF(byid, "The Account (%s) is not on the database", banusername);
            }
        }
    }
    MySQL_Bind(stmt_getUID, 0, banusername);
    MySQL_ExecuteParallel_Inline(stmt_getUID, using inline OnPlayerOffBan);
    return 1;
}

void:Ban_RemoveUser(username[], playerid = INVALID_PLAYER_ID)
{
    new
        string[45 + MAX_PLAYER_NAME],
        name[MAX_PLAYER_NAME];
    strcpy(name, username, MAX_PLAYER_NAME);

    inline OnPlayerRemoveBan() {
        if(!cache_num_rows()) {
            if(playerid != INVALID_PLAYER_ID) {
                SendServerMsgF(playerid, "The account "C_GREY"(%s) "C_WHITE"you're trying to unban is not in the database.", name);
                Logger_Dbg(ADMIN_DEBUG_HANDLER, "admin attempted to unban", Logger_P(playerid), Logger_S("username", name));
                return;
            }
        }

        mysql_format(MySQL_GetHandle(), string, sizeof(string), "DELETE FROM bans WHERE username = '%e'", name);
        mysql_tquery(MySQL_GetHandle(), string);
        if(playerid != INVALID_PLAYER_ID) {
            SendServerMsgF(playerid, "You successfully unbanned "C_GREY"%s's "C_WHITE"account.", name);
            Logger_Dbg(ADMIN_DEBUG_HANDLER, "admin has successfully unbanned", Logger_P(playerid), Logger_S("username", name));
        }
    }

    static const query[] = "\
    SELECT \
        username \
    FROM \
        bans \
    WHERE \
        username = '%e' \
    ";
    MySQL_TQueryInline(MySQL_GetHandle(), using inline OnPlayerRemoveBan, query, username, playerid);
}

void:Ban_CheckUser(playerid)
{
    new
        playerIP[20],
        playerGCPI[60],
        playerName[MAX_PLAYER_NAME];
    GetPlayerIp(playerid, playerIP, sizeof(playerIP));
    gpci(playerid, playerGCPI, sizeof(playerGCPI));
    GetPlayerName(playerid, playerName, sizeof(playerName));

    inline OnPlayerBanLoad() {
        new
            banIP[16 + 1],
            banName[MAX_PLAYER_NAME],
            banAdmin[MAX_PLAYER_NAME],
            banReason[MAX_BAN_REASON],
            banDate[40],
            unbanDate[40],
            expired;
        if(cache_num_rows()) {
            cache_get_value_name(0, "username", banName, MAX_PLAYER_NAME);
            cache_get_value_name(0, "ip",  banIP, 20);
            cache_get_value_name(0, "admin", banAdmin, MAX_PLAYER_NAME);
            cache_get_value_name(0, "reason", banReason, MAX_BAN_REASON);

            cache_get_value_name(0, "date_ban", banDate, 40);
            cache_get_value_name(0, "date_unban", unbanDate, 40);

            cache_get_value_name_int(0, "expired", expired);

            if(expired <= 0) {
                SendMsgF(playerid, COLOR_WHITE, "Your ban expired on "C_GREY"%s "C_WHITE"\nWelcome Back %p (%d), don't break any rules again!", unbanDate, playerid, playerid);
                Ban_RemoveUser(banName);
            }
            else {
                Kick(playerid);
            }
        } else {
            print("Player isn't banned");
            CallLocalFunction("OnPlayerPassedBanCheck", "i", playerid);
        }
    }

    MySQL_Bind(stmt_checkBan, 0, playerName);
    MySQL_Bind(stmt_checkBan, 1, playerGCPI);
    MySQL_Bind(stmt_checkBan, 2, playerIP);

    MySQL_ExecuteParallel_Inline(stmt_checkBan, using inline OnPlayerBanLoad);
}