#include <YSI_Coding\y_hooks>

static
    Statement: stmt_insertPlayerStats,
    Statement: stmt_loadPlayerStats
;

static 
    gPlayerScore[MAX_PLAYERS],
    gPlayerKills[MAX_PLAYERS],
    gPlayerDeaths[MAX_PLAYERS],
    gPlayerCoins[MAX_PLAYERS],
    gPlayerSkin[MAX_PLAYERS]
;

hook OnMySQLConnected()
{
    static const insertQuery[] = "\
    INSERT INTO \
        player_stats (u_id) \
    VALUES \
        (?) \
    ";
    stmt_insertPlayerStats = MySQL_PrepareStatement(MySQL_GetHandle(), insertQuery);

    static const loadQuery[] = "\
    SELECT \
        kills, \
        deaths, \
        coins, \
        score \
    FROM \
        player_stats \
    WHERE \
        u_id = ? \
    ";
    stmt_loadPlayerStats = MySQL_PrepareStatement(MySQL_GetHandle(), loadQuery);
    return 1;
}

hook OnPlayerRegister(playerid)
{
    MySQL_BindInt(stmt_insertPlayerStats, 0, Player_GetAccountID(playerid));
    MySQL_ExecuteThreaded(stmt_insertPlayerStats);
    return 1;
}

hook OnPlayerLogin(playerid)
{
    inline OnPlayerStatsLoad() {
        new 
            kills,
            deaths,
            coins,
            score;
        MySQL_BindResultInt(stmt_loadPlayerStats, 0, kills);
        MySQL_BindResultInt(stmt_loadPlayerStats, 1, deaths);
        MySQL_BindResultInt(stmt_loadPlayerStats, 2, coins);
        MySQL_BindResultInt(stmt_loadPlayerStats, 3, score);

        if(MySQL_Statement_FetchRow(stmt_loadPlayerStats)) {
            Player_SetKills(playerid, kills, false);
            Player_SetDeaths(playerid, deaths, false);
            Player_SetScore(playerid, score, false);
            Player_SetCoins(playerid, coins, false);
        }
    }
    MySQL_BindInt(stmt_loadPlayerStats, 0, Player_GetAccountID(playerid));
    MySQL_ExecuteParallel_Inline(stmt_loadPlayerStats, using inline OnPlayerStatsLoad);
    return 1;
}

stock Player_GetKills(playerid) return gPlayerKills[playerid];
stock Player_GetDeaths(playerid) return gPlayerDeaths[playerid];
stock Player_GetScore(playerid) return gPlayerScore[playerid];
stock Player_GetSkin(playerid) return gPlayerSkin[playerid];

stock Player_SetKills(playerid, value, bool:save = true)
{
    new string[256];
    gPlayerKills[playerid] = value;
    if(save) {
        static const query[] = "\
        UPDATE \
            player_stats \
        SET \
            kills = %d \
        WHERE \
            u_id = %d \
        ";
        mysql_format(MySQL_GetHandle(), string, sizeof string, query, value, Player_GetAccountID(playerid));
        mysql_tquery(MySQL_GetHandle(), string);
    }
}

stock Player_GiveKills(playerid)
{
    new totalKills = gPlayerKills[playerid] + 1;
    Player_SetKills(playerid, totalKills);
}

stock Player_SetDeaths(playerid, value, bool:save = true)
{
    new string[256];
    gPlayerDeaths[playerid] = value;
    if(save) {
        static const query[] = "\
        UPDATE \
            player_stats \
        SET \
            deaths = %d \
        WHERE \
            u_id = %d \
        ";
        mysql_format(MySQL_GetHandle(), string, sizeof string, query, value, Player_GetAccountID(playerid));
        mysql_tquery(MySQL_GetHandle(), string);
    }
}

stock Player_GiveDeath(playerid)
{
    new totalDeaths = gPlayerDeaths[playerid] + 1;
    Player_SetDeaths(playerid, totalDeaths);
}

stock Player_SetScore(playerid, value, bool:save = true)
{
    new string[256];
    gPlayerScore[playerid] = value;
    if(save) {
        static const query[] = "\
        UPDATE \
            player_stats \
        SET \
            score = %d \
        WHERE \
            u_id = %d \
        ";
        mysql_format(MySQL_GetHandle(), string, sizeof string, query, value, Player_GetAccountID(playerid));
        mysql_tquery(MySQL_GetHandle(), string);
    }
    SetPlayerScore(playerid, gPlayerScore[playerid]);
}

stock Player_GiveScore(playerid) 
{
    new totalScore = gPlayerScore[playerid] + 1;
    Player_SetScore(playerid, totalScore);
}

stock Player_SetCoins(playerid, value, bool:save = true)
{
    new string[256];
    gPlayerCoins[playerid] = value;
    if(save) {
        static const query[] = "\
        UPDATE \
            player_stats \
        SET \
            coins = %d \
        WHERE \
            u_id = %d \
        ";
        mysql_format(MySQL_GetHandle(), string, sizeof string, query, value, Player_GetAccountID(playerid));
        mysql_tquery(MySQL_GetHandle(), string);
    }
}

stock Player_GiveCoins(playerid, value)
{
    new totalCoins = gPlayerCoins[playerid] + value;
    Player_SetCoins(playerid, totalCoins);
}

stock Player_TakeCoins(playerid, value)
{
    new totalCoins = gPlayerCoins[playerid] - value;
    Player_SetCoins(playerid, totalCoins);
}

stock Player_SetSkin(playerid, skin, bool:setskin = true, bool:save = true)
{
    new string[256];
    gPlayerSkin[playerid] = skin;
    if(save) {
        static const query[] = "\
        UPDATE \
            player_stats \
        SET \
            skin = %d \
        WHERE \
            u_id = %d \
        ";
        mysql_format(MySQL_GetHandle(), string, sizeof string, query, skin, Player_GetAccountID(playerid));
        mysql_tquery(MySQL_GetHandle(), string);
    }
    if(setskin) {
        SetPlayerSkin(playerid, skin);
    }
}