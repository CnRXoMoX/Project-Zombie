#include <YSI_Coding\y_hooks>

hook OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
    if(PRESSED(KEY_NO)) 
    {
        ShowPlayerClosestLoots(playerid);
    }
    return 1;
}

ShowPlayerClosestLoots(playerid)
{
    new 
        count = 0,
        tmpString[100],
        originalString[512]
    ;
    
    foreach(new i : gLootIter)
    {
        new Float:x, Float:y, Float:z;
        GetLootSpawn(i, x, y, z);
        if(IsPlayerInRangeOfPoint(playerid, 3.0, x, y, z)) {
            if(!loot_Data[i][loot_pickupable]) {
                Logger_Log("[Error]: Loot is not pickupable! continuing",
                    Logger_I("Loot ID", i));
                continue;
            }
            new ItemID = loot_Data[i][loot_itemID];
            if(count == 0) {
                format(tmpString, sizeof(tmpString), "%s", GetItemNameFromID(ItemID));
            } else {
                format(tmpString, sizeof(tmpString), "\n%s", GetItemNameFromID(ItemID));
            }
            strcat(originalString, tmpString);
            format(tmpString, sizeof(tmpString), "NearbyLoot_%i", count);
            SetPVarInt(playerid, tmpString, i);
            count++;
        }
        if(count == 10) break;
    }

    inline OnPlayerPickupNearbyLoots(pid, dialogid, response, listitem, string:inputtext[]) {
        #pragma unused pid, dialogid, inputtext
        if(!response) return 1;

        if(!PlayerHasAvailableBagSlot(playerid)) return SendErrorMsg(playerid, "You have full items!");
        format(tmpString, sizeof(tmpString), "NearbyLoot_%i", listitem);
        new lootID = GetPVarInt(playerid, tmpString);
        new itemID = loot_Data[lootID][loot_itemID];

        if(!IsValidItem(itemID)) {
            Logger_Log("[loot-pickup]: Invalid Loot ID selection", 
                Logger_I("Loot ID", lootID),
                Logger_P(playerid));
            return 1;
        }
        
        GivePlayerItem(playerid, itemID);
        DeleteLoot(lootID);
        ShowPlayerClosestLoots(playerid);
    }
    
    if(count != 0) {
        format(tmpString, sizeof(tmpString), "Nearby loots %d", count);
        Dialog_ShowCallback(playerid, using inline OnPlayerPickupNearbyLoots, DIALOG_STYLE_LIST, tmpString, originalString, "Pickup", "Close");
    }
    return 1;
}