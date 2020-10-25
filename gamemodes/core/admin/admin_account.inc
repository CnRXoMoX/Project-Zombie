#include <YSI_Coding\y_hooks>
//#include <YSI_Data\y_bits>

enum 
{
    ADM_LVL_1 = 1,
    ADM_LVL_2,
    ADM_LVL_3,
    ADM_LVL_4,
    ADM_LVL_5
}

static 
    gPlayerAdminLevel[MAX_PLAYERS],
    //BitArray:gAdminOnDuty<MAX_PLAYERS>,
    Statement: stmt_getAdminLevel,
    Statement: stmt_insertAdminLevel
;

hook OnGameModeInit()
{
    repeat PruneAllLevelZero();
    return 1;
}

hook OnPlayerConnect(playerid)
{
    gPlayerAdminLevel[playerid] = 0;
    return 1;
}

hook OnMySQLConnected()
{
    static const loadQuery[] = "\
        SELECT \
            admin_level \
        FROM \
            admins \
        WHERE \
            u_id = ? \
        ";
    stmt_getAdminLevel = MySQL_PrepareStatement(MySQL_GetHandle(), loadQuery);

    static const insertQuery[] = "\
        INSERT INTO \
            admins (u_id, admin_level) \
        VALUES \
            (?,?) \
        ON DUPLICATE KEY UPDATE \
            admin_level = ?";
    stmt_insertAdminLevel = MySQL_PrepareStatement(MySQL_GetHandle(), insertQuery);
}

hook OnPlayerLogin(playerid)
{
    inline const OnAdminLoad()
    {
        new
            adminLevel;
        MySQL_BindResultInt(stmt_getAdminLevel, 0, adminLevel);

        if(MySQL_Statement_FetchRow(stmt_getAdminLevel)) {
            Player_SetAdminLevel(playerid, adminLevel);
            foreach(new i : Player)
            {
                if(Player_GetAdminLevel(i) != 0)
                {
                    SendMsgF(i, COLOR_PINK, "[ADMIN]: %p (%d) has logged in with %s", playerid, playerid, Admin_GetRankName(playerid));
                }
            }
        }
    }
    MySQL_BindInt(stmt_getAdminLevel, 0, Player_GetAccountID(playerid));
    MySQL_ExecuteThreaded_Inline(stmt_getAdminLevel, using inline OnAdminLoad);
    return 1;
}

stock Admin_GetRankName(playerid)
{
    new admin_RankNames[6][24] =
    {
        "None",             // 0
        "Trial Moderator",  // 1
        "Moderator",        // 2
        "Administator",     // 3
        "Head Adminitrator",// 4
        "Developer"         // 5
    };

    return admin_RankNames[Player_GetAdminLevel(playerid)];
}

timer KickTimer[500](playerid)
{
    Kick(playerid);
}

timer PruneAllLevelZero[10000]()
{
    mysql_tquery(MySQL_GetHandle(), "SELECT * FROM admins", "OnRowsCheck", "");
}

forward OnRowsCheck();
public OnRowsCheck()
{
    new rows;
    cache_get_row_count(rows);

    if(rows)
    {
        mysql_tquery(MySQL_GetHandle(), "DELETE FROM admins WHERE admin_level = 0");
        Logger_Log("Pruning all Admin level 0...");
    }
}

stock Player_SetAdminLevel(playerid, level)
{
    gPlayerAdminLevel[playerid] = level;
    MySQL_BindInt(stmt_insertAdminLevel, 0, Player_GetAccountID(playerid));
    MySQL_BindInt(stmt_insertAdminLevel, 1, level);
    MySQL_BindInt(stmt_insertAdminLevel, 2, level);
    MySQL_ExecuteThreaded(stmt_insertAdminLevel);
}

stock Player_GetAdminLevel(playerid)
{
    return gPlayerAdminLevel[playerid];
}

stock SendAdminCmdUsage(playerid, const cmd[], const cmdparam[])
{
    //new msg2[250];
    if(Player_GetAdminLevel(playerid) == 5) {
        return 0;
    }
    foreach(new i : Player)
    {
        if (i != INVALID_PLAYER_ID && Player_GetAdminLevel(i) > 0)
        {
            SendMsgF(i, COLOR_LIGHTGREEN, "[ADMINCMD]: %p (%d) used %s %s", playerid, playerid, cmd, cmdparam);
        }
    }
    //format(msg2, sizeof(msg2), "[ADMINCOMMAND]:%p (%d) used %s %s", playerid, playerid, cmd, cmdparam);
    //DCC_SendChannelMessage(cmdlogs_Discord_Chat, msg2);
    return 1;
}