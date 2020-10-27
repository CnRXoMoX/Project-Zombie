#define MAX_BAG_SLOTS           (64)

#define INVALID_SLOT_ID         (-1)

// Accessed global
new
    Iterator:gBagSlots[MAX_PLAYERS]<MAX_BAG_SLOTS>
;

static
    gPlayerItemInSlot[MAX_PLAYERS][MAX_BAG_SLOTS]
;

stock GivePlayerItem(playerid, iId)
{
    if(!IsValidItem(iId)) {
        Logger_Err("[NOT A VALID ITEM!] This is not a valid item",
            Logger_S("Function", "GivePlayerItem"));
        return 0;
    }
    new freebagslot = Iter_Free(gBagSlots[playerid]);
    if(freebagslot > Player_GetBagSlots(playerid)) return INVALID_SLOT_ID;
    Iter_Add(gBagSlots[playerid], freebagslot);
    gPlayerItemInSlot[playerid][freebagslot] = iId;
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
    if(drop) {   
        AddStaticLootItem(Player_GetItemInSlot(playerid, slotid), x, y, z - 1.0); 
    }
    gPlayerItemInSlot[playerid][slotid] = INVALID_ITEM_ID;
    return 1;
}