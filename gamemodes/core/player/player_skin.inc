#include <YSI_Coding\y_hooks>

static 
    gPlayerSkin[MAX_PLAYERS]
;

static
    Statement: stmt_playerSaveSkin
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

#define MAX_SKIN_NAME   (32)

/* SKINS */
enum E_RANDOM_SKINS_DATA
{
    E_RAND_SKIN_NAME[MAX_PLAYERS],
    E_RAND_SKIN_ID,
    E_SKIN_GENDER
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