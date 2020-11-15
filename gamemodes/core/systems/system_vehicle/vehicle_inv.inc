#include <YSI_Coding\y_hooks>

#define MAX_VEHICLE_SLOTS   (8)

static
    gVehicleItemInSlot[MAX_VEHICLES][MAX_VEHICLE_SLOTS],
    gVehicleSlotsUsed[MAX_VEHICLES]
;

hook OnDayZVehicleCreate(vehicleid)
{
    for(new i; i < MAX_VEHICLE_SLOTS; i++) {
        gVehicleItemInSlot[vehicleid][i] = INVALID_ITEM_ID;
    }
    return 1;
}

stock GiveVehicleItem(vehicleid, itemID) {
    if(!IsValidItem(iId)) {
        Logger_Err("[NOT A VALID ITEM!] This is not a valid item",
            Logger_S("Function", "GiveVehicleItem"));
        return 0;
    }
    if(gVehicleSlotsUsed[vehicleid] == MAX_VEHICLE_SLOTS) {
        return 0;
    }
    gVehicleItemInSlot
    gVehicleItemInSlot[vehicleid][freevehinvslot] = itemID;
    return freevehinvslot;
}

stock GetVehicleItemFromSlot(vehicleid, slotid) {
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
    if(gVehicleSlotsUsed[vehicleid] == MAX_VEHICLE_SLOTS) {
        return 0;
    }
    if(!IsPlayerHaveItem(playerid, itemID)) {
        Logger_Err("[ERROR]: Player don't have the item", 
            Logger_S("Function", "GiveVehicleItemFromPlayer"),
            Logger_P(playerid));
        return 0;
    }
    RemovePlayerItemInSlot(playerid, slotid);
    gVehicleItemInSlot[vehicleid][vehslotid] = itemID;
    gVehicleSlotsUsed[vehicleid]++;
    return 1;
}

stock RemoveVehicleItem(vehicleid, slotid)
{
    gVehicleItemInSlot[vehicleid][slotid] = INVALID_ITEM_ID;
    gVehicleSlotsUsed[vehicleid]--;
}

stock GivePlayerItemFromVehicle(playerid, vehicleid, vehslotid) 
{
    new itemID = GetVehicleItemFromSlot(vehicleid, vehslotid);
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
    for(new i; i < MAX_VEHICLE_SLOTS; i++) {
        gVehicleItemInSlot[vehicleid][i] = INVALID_ITEM_ID;
        gVehicleSlotsUsed[vehicleid]--;
    }
    return 1;
}