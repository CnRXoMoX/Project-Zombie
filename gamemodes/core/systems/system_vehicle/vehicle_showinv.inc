#include <YSI_Coding\y_hooks>

CMD:showvehinv(playerid, params[])
{
    foreach(new i : Vehicle)
    {
        if(!IsDayZVehicle(i)) continue;

        new Float:x, Float:y, Float:z;
        GetVehiclePos(i, x, y, z);
        printf("%d is a dayz vehicle", i);
        if(IsPlayerInRangeOfPoint(playerid, 5.0, x, y, z))
        {
            printf("%d is near the player", i);
            Player_ShowInvOfVehicleid(playerid, i);
            break;
        }
    }
    return 1;
}

hook OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
    if(PRESSED(KEY_FIRE))
    {
        for(new i; i < MAX_VEHICLES; i++)
        {
            if(!IsDayZVehicle(i)) continue;

            new Float:x, Float:y, Float:z;
            GetVehiclePos(i, x, y, z);
            printf("%d is a dayz vehicle", i);
            if(IsPlayerInRangeOfPoint(playerid, 5.0, x, y, z))
            {
                printf("%d is near the player showing shits", i);
                Player_ShowInvOfVehicleid(playerid, i);
                break;
            }
        }
    }
    return 1;
}

stock Player_ShowInvOfVehicleid(playerid, vehicleid)
{
    new
        count = 0,
        tmpString[100],
        origString[512];
    
    foreach(new i : gVehInv[vehicleid])
    {  
        new itemID = GetVehicleIDFromSlot(vehicleid, i);
        if(!IsValidItem(itemID)) {
            Logger_Log("[INVALID ITEM ID]: This is a invalid id marking as no loot", 
                Logger_S("Function", "Player_ShowInvOfVehicleid"),
                Logger_I("Item ID", itemID));
            strcat(origString, "No item");
            format(tmpString, sizeof(tmpString), "VehInv_%i", count);
            SetPVarInt(playerid, tmpString, i);
            count++;
        } else {
            if(count == 0) {
                format(tmpString, sizeof(tmpString), "%s", GetItemNameFromID(itemID));
            } else {
                format(tmpString, sizeof(tmpString), "\n%s", GetItemNameFromID(itemID));
            }
            strcat(origString, tmpString);
            format(tmpString, sizeof(tmpString), "VehInv_%i", count);
            SetPVarInt(playerid, tmpString, i);
            count++;
        }
    }

    inline _response(pid, dialogid, response, listitem, string:inputtext[]) {
        #pragma unused pid, dialogid, inputtext
        if(!response) return 1;
        format(tmpString, sizeof(tmpString), "VehInv_%i", listitem);
        new slotid = GetPVarInt(playerid, tmpString);
        new itemID = GetVehicleIDFromSlot(vehicleid, slotid);

        if(!IsValidItem(itemID)) {
            Player_ShowInvToPut(playerid, vehicleid, slotid);
            return 1;
        }
        GivePlayerItemFromVehicle(playerid, vehicleid, slotid);
        Player_ShowInvOfVehicleid(playerid, vehicleid);
    }
    Dialog_ShowCallback(playerid, using inline _response, DIALOG_STYLE_LIST, "Items", origString, "Select", "Close");
    return 1;
}

Player_ShowInvToPut(playerid, vehicleid, slotid)
{
    new
        count = 0,
        tmpString[100],
        origString[512];
    
    foreach(new i : gBagSlots[playerid])
    {
        if(!IsValidItem(Player_GetItemInSlot(playerid, i))) {
            Logger_Log("[LOOT-INVENTORY]: Loot is invalid! continuing", 
                Logger_P(playerid),
                Logger_I("Item ID", Player_GetItemInSlot(playerid, i)));
            continue;
        }
        if(count == 0) {
            format(tmpString, sizeof(tmpString), "%s", GetItemNameFromID(Player_GetItemInSlot(playerid, i)));
        } else {
            format(tmpString, sizeof(tmpString), "\n%s", GetItemNameFromID(Player_GetItemInSlot(playerid, i)));
        }
        strcat(origString, tmpString);
        format(tmpString, sizeof(tmpString), "InvTextMenu_%i", count);
        SetPVarInt(playerid, tmpString, i);
        count++;
    }

    inline _response(pid, dialogid, response, listitem, string:inputtext[]) {
        #pragma unused pid, dialogid, inputtext
        format(tmpString, sizeof(tmpString), "InvTextMenu_%i", listitem);
        new slotid2 = GetPVarInt(playerid, tmpString);
        new itemID = Player_GetItemInSlot(playerid, slotid2);

        if(!response) return 1;

        if(!IsValidItem(itemID)) {
            Logger_Log("[INVALID ITEM]: This is an invalid item", 
                Logger_S("Function", "Player_ShowInvToPut"),
                Logger_P(playerid),
                Logger_I("Item ID", itemID));
            return 1;
        }
        GiveVehicleItemFromPlayer(playerid, vehicleid, slotid2, slotid);
    }

    if(count != 0) {
        Dialog_ShowCallback(playerid, using inline _response, DIALOG_STYLE_LIST, "Inventory", origString, "Select", "Close");
    } else {
        SendServerMsg(playerid, "You don't have any items in inventory");
    }
    return 1;
}