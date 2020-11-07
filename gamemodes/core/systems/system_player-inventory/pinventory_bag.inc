#include <YSI_Coding\y_hooks>

#define MAX_BAG_1_ITEMS         (8)
#define MAX_BAG_2_ITEMS         (16)
#define MAX_BAG_3_ITEMS         (32)
#define MAX_BAG_4_ITEMS         (64)

/* Variables */
static
    gPlayerBagLvl[MAX_PLAYERS],
    gPlayerBagSlots[MAX_PLAYERS],
    bool:gPlayerHasSavedBag[MAX_PLAYERS]
;

/* Statements */
static
    Statement: stmt_playerBagSave,
    Statement: stmt_playerBagLoad
;

hook OnMySQLConnected() 
{
    static const saveQuery[] = "\
    INSERT INTO players_bag(u_id, baglevel)\
    VALUES (?,?)\
    ON DUPLICATE KEY UPDATE baglevel = ? \
    ";
    stmt_playerBagSave = MySQL_PrepareStatement(MySQL_GetHandle(), saveQuery);

    static const loadQuery[] = "\
    SELECT \
        baglevel \
    FROM \
        players_bag \
    WHERE \
        u_id = ? \
    ";
    stmt_playerBagLoad = MySQL_PrepareStatement(MySQL_GetHandle(), loadQuery);
    return 1;
}

hook OnPlayerConnect(playerid)
{
    gPlayerHasSavedBag[playerid] = false;
    return 1;
}

hook OnPlayerLogin(playerid)
{
    inline OnDataLoad()
    {
        new
            bag;
        MySQL_BindResultInt(stmt_playerBagLoad, 0, bag);

        if(MySQL_Statement_FetchRow(stmt_playerBagLoad)) {
            gPlayerBagLvl[playerid] = bag;
            gPlayerHasSavedBag[playerid] = true;
        }
    }
    MySQL_BindInt(stmt_playerBagLoad, 0, Player_GetAccountID(playerid));
    MySQL_ExecuteParallel_Inline(stmt_playerBagLoad, using inline OnDataLoad);
    return 1;
}

hook OnPlayerSpawn(playerid)
{
    if(gPlayerHasSavedBag[playerid]) {
        gPlayerHasSavedBag[playerid] = false;
        GivePlayerBag(playerid, gPlayerBagLvl[playerid]);
    }
    return 1;
}

stock GetBagSlots(lvl) {
    new baglevel;
    switch(lvl) {
        case 1: baglevel = MAX_BAG_1_ITEMS;
        case 2: baglevel = MAX_BAG_2_ITEMS;
        case 3: baglevel = MAX_BAG_3_ITEMS;
        case 4: baglevel = MAX_BAG_4_ITEMS;
        default: baglevel = MAX_BAG_1_ITEMS;
    }
    return baglevel;
}

stock GivePlayerBagObject(playerid, lvl) {
    switch(lvl) {
        case 1: print("Not yet used");
        case 2: print("Not yet used");
        case 3:
        {
            RemovePlayerAttachedObject(playerid, 0);
            SetPlayerAttachedObject(playerid, 0, 11745, 1, -0.060999, -0.128000, 0.000000, 87.599967, 177.999923, 87.899986, 1.000000, 1.000000, 1.000000);
        }
        case 4: print("Not yet used");
    }
}

stock GivePlayerBag(playerid, lvl) {
    GivePlayerBagObject(playerid, lvl);
    gPlayerBagLvl[playerid] = lvl;
    gPlayerBagSlots[playerid] = GetBagSlots(lvl);
    MySQL_BindInt(stmt_playerBagSave, 0, Player_GetAccountID(playerid));
    MySQL_BindInt(stmt_playerBagSave, 1, lvl);
    MySQL_BindInt(stmt_playerBagSave, 2, lvl);
    MySQL_ExecuteThreaded(stmt_playerBagSave);
}

stock Player_GetBagSlots(playerid) return gPlayerBagSlots[playerid];
stock Player_GetBagLevel(playerid) return gPlayerBagLvl[playerid];

hook OnPlayerUpdate(playerid)
{
    if(gPlayerBagSlots[playerid] != GetBagSlots(gPlayerBagLvl[playerid])) {
        // Anti bug i guess? but we need to investigate tho xd
        GivePlayerBag(playerid, gPlayerBagLvl[playerid]);
    }
    return 1;
}