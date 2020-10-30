#include <YSI_Coding\y_hooks>
#define MAX_BAG_SLOTS           (64)

#define INVALID_SLOT_ID         (-1)

// Accessed global
new
    Iterator:gBagSlots[MAX_PLAYERS]<MAX_BAG_SLOTS>
;

static
    Statement: stmt_insertItem,
    Statement: stmt_loadItems,
    Statement: stmt_deleteItem
;

static
    gPlayerItemInSlot[MAX_PLAYERS][MAX_BAG_SLOTS]
;

hook OnMySQLConnected()
{
    static const insertQuery[] = "\
    INSERT INTO \
        players_lootinv (u_id, slot, item_id) \
    VALUES \
        (?,?,?) \
    ";
    stmt_insertItem = MySQL_PrepareStatement(MySQL_GetHandle(), insertQuery);

    static const loadQuery[] = "\
    SELECT \
        slot, \
        item_id \
    FROM \
        players_lootinv \
    WHERE \
        u_id = ? \
    ";
    stmt_loadItems = MySQL_PrepareStatement(MySQL_GetHandle(), loadQuery);

    static const deleteQuery[] = "\
    DELETE FROM \
        players_lootinv \
    WHERE \
        u_id = ? AND slot = ? \
    ";
    stmt_deleteItem = MySQL_PrepareStatement(MySQL_GetHandle(), deleteQuery);
    return 1;
}

static
    bool:gPlayerJustLoggedIn[MAX_PLAYERS],
    gPlayerLoots[MAX_PLAYERS]
;

hook OnPlayerConnect(playerid)
{
    gPlayerJustLoggedIn[playerid] = false;
    gPlayerLoots[playerid] = 0;
    return 1;
}

hook OnPlayerDisconnect(playerid, reason)
{
    new count = 0;
    foreach(new i : Player)
    {
        if(count == MAX_BAG_SLOTS) break;
        Iter_Remove(gBagSlots[playerid], i);
        count++;
    }
    return 1;
}

hook OnPlayerSpawn(playerid)
{
    if(gPlayerJustLoggedIn[playerid] && gPlayerLoots[playerid] != 0)
    {
        SendServerMsgF(playerid, "You've just loaded with %d loots!", gPlayerLoots[playerid]);
        gPlayerJustLoggedIn[playerid] = false;
        gPlayerLoots[playerid] = 0;
    }
    return 1;
}

hook OnPlayerLogin(playerid)
{
    inline OnPlayerLoadItems()
    {
        new
            slot,
            itemID;
        MySQL_BindResultInt(stmt_loadItems, 0, slot);
        MySQL_BindResultInt(stmt_loadItems, 1, itemID);

        while(MySQL_Statement_FetchRow(stmt_loadItems)) {
            GivePlayerItemInSlot(playerid, itemID, slot);
            gPlayerLoots[playerid]++;
            gPlayerJustLoggedIn[playerid] = true;
        }
    }
    MySQL_BindInt(stmt_loadItems, 0, Player_GetAccountID(playerid));
    MySQL_ExecuteParallel_Inline(stmt_loadItems, using inline OnPlayerLoadItems);
    return 1;
}

stock GivePlayerItemInSlot(playerid, iId, slot)
{
    if(!IsValidItem(iId)) {
        Logger_Err("[NOT A VALID ITEM!] This is not a valid item",
            Logger_S("Function", "GivePlayerItemInSlot"));
        return 0;
    }

    if(Iter_Contains(gBagSlots[playerid], slot)) {
        Logger_Err("[ERROR]: SLOT IS BEING USED!",
            Logger_S("Function", "GivePlayerItemInSlot"),
            Logger_I("Slot", slot),
            Logger_P(playerid));
        return 0;
    }
    Iter_Add(gBagSlots[playerid], slot);
    gPlayerItemInSlot[playerid][slot] = iId;
    return 1;
}

stock bool:PlayerHasAvailableBagSlot(playerid) {
    new freebagslot = Iter_Free(gBagSlots[playerid]);
    if(freebagslot <= Player_GetBagSlots(playerid)) {
        return true;
    }
    return false;
}

stock GivePlayerItem(playerid, iId)
{
    if(!IsValidItem(iId)) {
        Logger_Err("[NOT A VALID ITEM!] This is not a valid item",
            Logger_S("Function", "GivePlayerItem"));
        return 0;
    }
    if(!PlayerHasAvailableBagSlot(playerid)) return INVALID_SLOT_ID;
    new freebagslot = Iter_Free(gBagSlots[playerid]);
    Iter_Add(gBagSlots[playerid], freebagslot);
    printf("%d", freebagslot);
    gPlayerItemInSlot[playerid][freebagslot] = iId;
    MySQL_BindInt(stmt_insertItem, 0, Player_GetAccountID(playerid));
    MySQL_BindInt(stmt_insertItem, 1, freebagslot);
    MySQL_BindInt(stmt_insertItem, 2, iId);
    MySQL_ExecuteThreaded(stmt_insertItem);
    return freebagslot;
}

stock Player_GetItemInSlot(playerid, slotid) {
    return gPlayerItemInSlot[playerid][slotid];
}

stock RemovePlayerItemInSlot(playerid, slotid, bool:drop = false)
{
    if(!IsValidItem(Player_GetItemInSlot(playerid, slotid))) {
        Logger_Err("[NOT A VALID ITEM!] This is not a valid item",
            Logger_S("Function", "RemovePlayerItem"),
            Logger_I("SlotId", slotid),
            Logger_P(playerid));
        return 0;
    }
    new Float:x, Float:y, Float:z;
    GetPlayerPos(playerid, x, y, z);
    Iter_Remove(gBagSlots[playerid], slotid);
    GetXYInFrontOfPlayer(playerid, x, y, 3.0);
    MySQL_BindInt(stmt_deleteItem, 0, Player_GetAccountID(playerid));
    MySQL_BindInt(stmt_deleteItem, 1, slotid);
    MySQL_ExecuteThreaded(stmt_deleteItem);
    if(drop) {   
        AddStaticLootItem(Player_GetItemInSlot(playerid, slotid), x, y, z - 1.0); 
    }
    gPlayerItemInSlot[playerid][slotid] = INVALID_ITEM_ID;
    return 1;
}

stock IsPlayerHaveItem(playerid, iId) {
    foreach(new i : gBagSlots[playerid])
    {
        if(gPlayerItemInSlot[playerid][i] == iId) {
            return 1;
        }
    }
    return 00;
}