#include <YSI_Coding\y_hooks>

hook OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
    if(PRESSED(KEY_NO))
    {
        for(new i; i < MAX_VEHICLES; i++)
        {
            if(!IsDayZVehicle(i)) continue;

            new Float:x, Float:y, Float:z;
            GetVehiclePos(i, x, y, z);
            if(IsPlayerInRangeOfPoint(playerid, 5.0, x, y, z))
            {
                Player_ShowInvOfVehicleid(playerid, i);
                break;
            }
        }
    }
    return 1;
}

stock Player_ShowInvOfVehicleid(playerid, vehid)
{
    new itemInSlot[MAX_VEHICLE_SLOTS], count = 0;
    new tmpString[128], origString[512];
    for(new i; i < MAX_VEHICLE_SLOTS; i++) {
        new itemID = GetVehicleItemFromSlot(vehid, i);
        if(!IsValidItem(itemID)) {
            itemInSlot[count] = INVALID_ITEM_ID;
            strcat(origString, "No Item\n");
            count++;
        } else {
            format(tmpString, sizeof(tmpString), "%s\n", GetItemNameFromID(itemID));
            strcat(origString, tmpString);
            itemInSlot[count] = itemID;
            count++;
        }
    }

    inline _response(pid, dialogid, response, listitem, string:inputtext[]) {
        #pragma unused pid, dialogid, inputtext
        if(!response) return 1;
        if(!IsValidItem(itemInSlot[listitem])) {
            Player_ShowInvToPut(playerid, vehid, listitem);      
        } else {
            GivePlayerItemFromVehicle(playerid, vehid, listitem);
        }
    }

    Dialog_ShowCallback(playerid, using inline _response, DIALOG_STYLE_LIST, "Items", origString, "Select", "Cancel");
    return 1;
}

stock Player_ShowInvToPut(playerid, vehicleid, slotid)
{
    new tmpString[128], origString[512];
    new count = 0;

    inline _response(pid, dialogid, response, listitem, string:inputtext[]) {
        #pragma unused pid, dialogid, inputtext
        if(!response) {
            Player_ShowInvOfVehicleid(playerid, vehicleid);
            return 1;
        }
        format(tmpString, sizeof(tmpString), "PlayerInv_%i", listitem);
        new pslotid = GetPVarInt(playerid, tmpString);
        new itemID = Player_GetItemInSlot(playerid, pslotid);

        if(!IsValidItem(itemID)) {
            Logger_Err("[NOT A VALID ITEM!] This is not a valid item",
                Logger_S("Function", "Player_ShowInvToPut"));
            Player_ShowInvOfVehicleid(playerid, vehicleid);
            return 0;
        }
        GiveVehicleItemFromPlayer(playerid, vehicleid, pslotid, slotid);
        Player_ShowInvOfVehicleid(playerid, vehicleid);
    }

    foreach(new i : gBagSlots[playerid])
    {
        new itemID = Player_GetItemInSlot(playerid, i);
        if(!IsValidItem(itemID)) {
            Logger_Log("[LOOT-INVENTORY]: Loot is invalid! continuing", 
                Logger_P(playerid),
                Logger_I("Item ID", itemID));
            continue;
        }
        if(count == 0) {
            format(tmpString, sizeof(tmpString), "%s", GetItemNameFromID(itemID));
        } else {
            format(tmpString, sizeof(tmpString), "\n%s", GetItemNameFromID(itemID));
        }
        strcat(origString, tmpString);
        format(tmpString, sizeof(tmpString), "PlayerInv_%i", count);
        SetPVarInt(playerid, tmpString, i);
        count++;
    }
    if(count != 0) {
        Dialog_ShowCallback(playerid, using inline _response, DIALOG_STYLE_LIST, "Your bag", origString, "Select", "Back");
    } else {
        SendErrorMsg(playerid, "You don't have any items");
        return Player_ShowInvOfVehicleid(playerid, vehicleid);
    }
    return 1;
}