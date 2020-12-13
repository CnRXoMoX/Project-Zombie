ACMD:[4]giveitem(playerid, params[])
{
    new lootName[MAX_LOOT_NAME];
    if(sscanf(params, "s[32]", lootName)) return SendSyntaxMsg(playerid, "/giveitem (item name)");
    if(strlen(lootName) > MAX_LOOT_NAME) return SendErrorMsgF(playerid, "loot name is supposed to be %d letters", MAX_LOOT_NAME);
    new itemID = GetItemIDFromName(lootName);
    if(!IsValidItem(itemID)) return SendErrorMsgF(playerid, "The item %s does not exist!", lootName);
    if(!PlayerHasAvailableBagSlot(playerid)) return SendErrorMsg(playerid, "You don't have any available bag slots");
    GivePlayerItem(playerid, itemID);
    return 1;
}