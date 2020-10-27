#include <YSI_Coding\y_hooks>

forward RequestToSeeNearbyLoots(playerid, listitem);
public RequestToSeeNearbyLoots(playerid, listitem)
{
    new tmpString[24];
    format(tmpString, sizeof(tmpString), "NearbyLoots_%i", listitem);
    new lootID = GetPVarInt(playerid, tmpString);
    new itemID = loot_Data[lootID][loot_itemID];

    if(!IsValidItem(itemID)) {
        Logger_Log("[loot-pickup]: Invalid Loot ID selection", 
            Logger_I("Loot ID", lootID),
            Logger_P(playerid));
        return 0;
    }

    DeleteLoot(itemID);
    GivePlayerItem(playerid, itemID);
    ShowPlayerClosestLoots(playerid);
    return 1;
}

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
        tmpString[100]
    ;
    TextMenu_Create(playerid, "RequestToSeeNearbyLoots", "~b~Nearby loots");
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
            print("player is near a loot");
            new ItemID = loot_Data[i][loot_itemID];
            format(tmpString, sizeof(tmpString), "~w~%s", GetItemNameFromID(ItemID));
            TextMenu_Add(playerid, tmpString);
            format(tmpString, sizeof(tmpString), "NearbyLoots_%i", count);
            SetPVarInt(playerid, tmpString, i);
            count++;
            printf("Loots counted near player %d", count);
        }
    }
    if(count != 0) {
        print("Showing the player now");
        TextMenu_Show(playerid);
    }
    return 1;
}