forward InventoryTextMenu(playerid, lstitem);
public InventoryTextMenu(playerid, lstitem)
{
    new tmpString[100];
    new string[126], string2[126];
    format(tmpString, sizeof(tmpString), "InvTextMenu_%i", lstitem);
    new slotid = GetPVarInt(playerid, tmpString);

    if(!IsValidItem(Player_GetItemInSlot(playerid, slotid))) {
        Logger_Log("[LOOT-ITEM]: error in callback InventoryTextMenu (Invalid ITEM)",
            Logger_P(playerid),
            Logger_I("Item ID", Player_GetItemInSlot(playerid, slotid)));
        return 0;
    }
    

    inline OnPlayerResponse(pid, dialogid, response, listitem, string:inputtext[]) {
        #pragma unused pid, dialogid, listitem, inputtext

        if(!response) {
            SendServerMsgF(playerid, "You have dropped your %s", GetItemNameFromID(Player_GetItemInSlot(playerid, slotid)));
            RemovePlayerItemInSlot(playerid, slotid, true);
        }
        else {
            PlayerUseItem(playerid, Player_GetItemInSlot(playerid, slotid));
            RemovePlayerItemInSlot(playerid, slotid);
        }
    }

    format(string, sizeof(string), "What to do with the item %s", GetItemNameFromID(Player_GetItemInSlot(playerid, slotid)));
    format(string2, sizeof(string2), "%s", GetItemNameFromID(Player_GetItemInSlot(playerid, slotid)));
    Dialog_ShowCallback(playerid, using inline OnPlayerResponse, DIALOG_STYLE_MSGBOX, string2, string, "Use", "Drop");
    return 1;
}

CMD:inv(playerid, params[])
{
    new 
        count = 1,
        tmpString[100];
    TextMenu_Create(playerid, "InventoryTextMenu", "~b~Inventory");
    foreach(new i : gBagSlots[playerid])
    {
        if(!IsValidItem(Player_GetItemInSlot(playerid, i))) {
            Logger_Log("[LOOT-INVENTORY]: Loot is invalid! continuing", 
                Logger_P(playerid),
                Logger_I("Item ID", Player_GetItemInSlot(playerid, i)));
            continue;
        }
        format(tmpString, sizeof(tmpString), "~w~%s", GetItemNameFromID(Player_GetItemInSlot(playerid, i)));
        TextMenu_Add(playerid, tmpString);
        format(tmpString, sizeof(tmpString), "InvTextMenu_%i", count);
        SetPVarInt(playerid, tmpString, i);
        count++;
    }
    if(count == 1) {
        SendServerMsg(playerid, "You don't have items in your inventory");
    } else {
        TextMenu_Show(playerid);
    }  
    return true;
}