#include <YSI_Coding\y_hooks>

#define MAX_SKIN_NAME   (32)
#define INVALID_SKIN_ID (-1)

static 
    gPlayerSkin[MAX_PLAYERS],
    bool:gPlayerHasSavedSkin[MAX_PLAYERS]
;

static
    Statement: stmt_playerSaveSkin,
    Statement: stmt_playerLoadSkin
;

hook OnMySQLConnected()
{
    static const query[] = "\
    UPDATE \
        players_stats \
    SET \
        skin = ? \
    WHERE \
        u_id = ? \
    ";
    stmt_playerSaveSkin = MySQL_PrepareStatement(MySQL_GetHandle(), query);

    static const loadQuery[] = "\
    SELECT \
        skin \
    FROM \
        players_stats \
    WHERE \
        u_id = ? \
    ";
    stmt_playerLoadSkin = MySQL_PrepareStatement(MySQL_GetHandle(), loadQuery);
    return 1;
}

hook OnPlayerHasAccount(playerid) 
{
    inline OnDataLoad() {
        new
            skin;
        MySQL_BindResultInt(stmt_playerLoadSkin, 0, skin);

        if(MySQL_Statement_FetchRow(stmt_playerLoadSkin)) {
            gPlayerSkin[playerid] = skin;
            gPlayerHasSavedSkin[playerid] = true;
        }
    }
    MySQL_BindInt(stmt_playerLoadSkin, 0,  Player_GetAccountID(playerid));
    MySQL_ExecuteParallel_Inline(stmt_playerLoadSkin, using inline OnDataLoad);
    return 1;
}

Player_SetSkin(playerid, skinid, bool:save = true) {
    SetPlayerSkin(playerid, skinid);
    gPlayerSkin[playerid] = skinid;
    if(save) {
        MySQL_BindInt(stmt_playerSaveSkin, 0, skinid);
        MySQL_BindInt(stmt_playerSaveSkin, 1, Player_GetAccountID(playerid));
        MySQL_ExecuteThreaded(stmt_playerSaveSkin);
    }
}

Player_GetSkin(playerid) return gPlayerSkin[playerid];

/* SKINS */
enum E_RANDOM_SKINS_DATA
{
    E_RAND_SKIN_NAME[MAX_PLAYERS],
    E_RAND_SKIN_ID,
    Gender:E_SKIN_GENDER
};

static 
    const randSkinData[][E_RANDOM_SKINS_DATA] =
{
    { "Rich Woman", 12, FEMALE},
    { "Stree Girl", 13, FEMALE},
    { "Chinese Woman", 169, FEMALE},
    { "Farmer", 34, MALE},
    { "Downtown Guy", 60, MALE},
    { "Cracker", 144, MALE}
};

stock GetRandSkin()
{
    new rand = random(sizeof(randSkinData));
    return randSkinData[rand][E_RAND_SKIN_ID];
}

stock GetPlayerSkinName(playerid) {
    new skinDataId;
    for(new i = 0; i < sizeof(randSkinData); i++) 
    {
        if(gPlayerSkin[playerid] == randSkinData[i][E_RAND_SKIN_ID])
        {
            return randSkinData[i][E_RAND_SKIN_NAME];
        }
    }
    return INVALID_SKIN_ID;
}

hook OnPlayerSpawn(playerid)
{
    if(Player_New(playerid) || IsPlayerJustDied(playerid)) {
        Player_SetSkin(playerid, GetRandSkin(), true);
    } else if(gPlayerHasSavedSkin[playerid]) {
        gPlayerHasSavedSkin[playerid] = false;
        Player_SetSkin(playerid, Player_GetSkin(playerid));
    }
    return 1;
}