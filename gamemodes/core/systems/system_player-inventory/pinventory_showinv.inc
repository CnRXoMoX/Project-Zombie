#include <YSI_Coding\y_hooks>

hook OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
    if(PRESSED(KEY_YES))
    {
        ShowPlayerInventory(playerid);
    }
    return 1;
}

ShowPlayerInventory(playerid)
{
    new
        count = 0,
        tmpString[100],
        originalString[512];
    
    inline OnPlayerSelectInInv(pid, dialogid, response, listitem, string:inputtext[]) {
        #pragma unused pid, dialogid, inputtext
        if(!response) return 1;
        
        new string[126], string2[126];
        format(tmpString, sizeof(tmpString), "InvTextMenu_%i", listitem);
        new slotid = GetPVarInt(playerid, tmpString);
        
        if(!IsValidItem(Player_GetItemInSlot(playerid, slotid))) {
            Logger_Log("[LOOT-ITEM]: error in callback InventoryTextMenu (Invalid ITEM)",
                Logger_P(playerid),
                Logger_I("Item ID", Player_GetItemInSlot(playerid, slotid)));
            return 0;
        }

        inline OnPlayerSelectWhatToDo(ppid, did, res, lstitem, string:inptext[]) {
            #pragma unused ppid, did, inptext, lstitem

            if(!res) {
                SendServerMsgF(playerid, "You have dropped your %s", GetItemNameFromID(Player_GetItemInSlot(playerid, slotid)));
                RemovePlayerItemInSlot(playerid, slotid, true);
            } else {
                PlayerUseItem(playerid, Player_GetItemInSlot(playerid, slotid));
                RemovePlayerItemInSlot(playerid, slotid);
            }
        }

        format(string, sizeof(string), "What to do with the item %s", GetItemNameFromID(Player_GetItemInSlot(playerid, slotid)));
        format(string2, sizeof(string2), "%s", GetItemNameFromID(Player_GetItemInSlot(playerid, slotid)));
        Dialog_ShowCallback(playerid, using inline OnPlayerSelectWhatToDo, DIALOG_STYLE_MSGBOX, string2, string, "Use", "Drop");
    }

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
        strcat(originalString, tmpString);
        format(tmpString, sizeof(tmpString), "InvTextMenu_%i", count);
        SetPVarInt(playerid, tmpString, i);
        count++;
    }

    if(count != 0) {
        format(tmpString, sizeof(tmpString), "Inventory (%d:%d)", count, Player_GetBagSlots(playerid));
        Dialog_ShowCallback(playerid, using inline OnPlayerSelectInInv, DIALOG_STYLE_LIST, tmpString, originalString, "Use", "Close");
    } else {
        SendServerMsg(playerid, "You don't have any items!");
    }
    return 1;
}