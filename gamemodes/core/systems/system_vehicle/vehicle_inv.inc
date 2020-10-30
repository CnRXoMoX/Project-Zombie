#define MAX_VEHICLE_SLOTS   (8)

new Iterator:gVehInv[MAX_VEHICLES]<MAX_VEHICLE_SLOTS>;

static
    gVehicleItemInSlot[MAX_VEHICLES][MAX_VEHICLE_SLOTS]
;


stock GiveVehicleItem(vehicleid, itemID) {
    if(!IsValidItem(iId)) {
        Logger_Err("[NOT A VALID ITEM!] This is not a valid item",
            Logger_S("Function", "GiveVehicleItem"));
        return 0;
    }
    new freevehinvslot = Iter_Free(gVehInv[vehicleid]);

    if (freevehinvslot == ITER_NONE) {
        return -1;
    }
    Iter_add(gVehInv[vehicleid], freevehinvslot);
    gVehicleItemInSlot[vehicleid][freevehinvslot] = itemID;
    return freevehinvslot;
}

stock GetVehicleIDFromSlot(vehicleid, slotid) {
    return gVehicleItemInSlot[vehicleid][slotid];
}

stock bool:IsValidVehicleSlot(slotid) {
    if(slotid < 0 || slotid > MAX_VEHICLE_SLOTS) {
        return false;
    }
    return true;
}

stock bool:IsValidVehicleID(vehicleid) {
    if(IsDayZVehicle(vehicleid)) {
        return true;
    }
    return false;
}

stock GiveVehicleItemFromPlayer(playerid, vehicleid, slotid, vehslotid)
{
    new itemID = Player_GetItemInSlot(playerid, slotid);
    if(!IsValidItem(itemID)) {
        Logger_Err("[NOT A VALID ITEM!] This is not a valid item",
            Logger_S("Function", "GiveVehicleItemFromPlayer"));
        return 0;
    }
    new freevehinvslot = Iter_Free(gVehInv[vehicleid]);

    if(freevehinvslot == ITER_NONE) {
        return -1;
    }
    if(!IsPlayerHaveItem(playerid, itemID)) {
        Logger_Err("[ERROR]: Player don't have the item", 
            Logger_S("Function", "GiveVehicleItemFromPlayer"),
            Logger_P(playerid));
        return 0;
    }
    RemovePlayerItemInSlot(playerid, slotid);
    gVehicleItemInSlot[vehicleid][vehslotid] = itemID;
    return 1;
}

stock RemoveVehicleItem(vehicleid, slotid)
{
    gVehicleItemInSlot[vehicleid][slotid] = INVALID_ITEM_ID;
    Iter_Remove(gVehInv[vehicleid], slotid);
}

stock GivePlayerItemFromVehicle(playerid, vehicleid, vehslotid) 
{
    new itemID = GetVehicleIDFromSlot(vehicleid, vehslotid);
    if(!IsValidItem(itemID)) {
        Logger_Err("[NOT A VALID ITEM!] This is not a valid item",
            Logger_S("Function", "GivePlayerItemFromVehicle"));
        return 0;
    }
    if(!PlayerHasAvailableBagSlot(playerid)) return SendServerMsg(playerid, "You don't have enough bag slot");
    RemoveVehicleItem(vehicleid, vehslotid);
    GivePlayerItem(playerid, itemID);
    return 1;
}

stock DeleteVehicleItems(vehicleid) {
    if(!IsValidVehicleID(vehicleid)) {
        Logger_Err("[NOT A VALID VEHICLE!]: This is not a valid vehicleid", 
            Logger_S("Function", "DeleteVehicleItems"));
        return 0;
    }
    foreach(new i : gVehInv[vehicleid])
    {
        gVehicleItemInSlot[vehicleid][i] = INVALID_ITEM_ID;
    }
    return 1;
}