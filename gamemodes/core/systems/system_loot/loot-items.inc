#include <YSI_Coding\y_hooks>

#define MAX_LOOT_NAME   (32)
#define MAX_ITEMS_ID    (sizeof(lootData))

#define INVALID_ITEM_ID (-1)

enum E_LOOT_DATA
{
    E_LOOT_OBJECT,
    E_LOOT_SPAWN_PERCENT,
    E_LOOT_NAME[MAX_LOOT_NAME],
}

new
    const lootData[][E_LOOT_DATA] =
{
    // First Aid Kits
    { 11747, 80, "Bandage" },
    { 11738, 80, "Medkit" },
    { 2709, 80, "Painkiller" },
    { 1577, 80, "Antibiotics" },
    { 11736, 80, "Morphine"}
};

stock bool:IsValidItem(iId)
{
    if(iId < 0 || iId > MAX_ITEMS_ID)
    {
        return false; 
    }
    return true;
}

stock GetItemIDFromName(const iname[])
{
    for(new i = 0; i < sizeof(lootData); i++)
    {
        if(!strcmp(lootData[i][E_LOOT_NAME], iname, true))
        {
            return lootData[i][E_LOOT_OBJECT];
        }
    }
    return INVALID_ITEM_ID;
}

stock GetItemNameFromID(iId)
{
    if(!IsValidItem(iId)) {
        Logger_Err("[loot-items] IVALID ITEM ID!", Logger_I("item id", iId));
        return 0;
    }
    return lootData[iId][E_LOOT_NAME];
}

stock GetObjectIDFromID(iId)
{
    if(!IsValidItem(iId)) { 
        Logger_Err("[loot-items] IVALID ITEM ID!", Logger_I("item id", iId));
        return 0;
    }
    return lootData[iId][E_LOOT_OBJECT];
}

stock GetObjectIDFromName(const iname[])
{
    for(new i = 0; i < sizeof(lootData); i++)
    {
        if(!strcmp(lootData[i][E_LOOT_NAME], iname, true))
        {
            return lootData[i][E_LOOT_OBJECT];
        }
    }
    return INVALID_ITEM_ID;
}

stock GetSpawnPercentFromID(iId)
{
    if(!IsValidItem(iId)){ 
        Logger_Err("[loot-items] IVALID ITEM ID!", Logger_I("item id", iId));
        return 0;
    }
    return lootData[iId][E_LOOT_SPAWN_PERCENT];
}

stock GetSpawnPercentFromName(const iname[])
{
    for(new i = 0; i < sizeof(lootData); i++)
    {
        if(!strcmp(lootData[i][E_LOOT_NAME], iname, true))
        {
            return lootData[i][E_LOOT_SPAWN_PERCENT];
        }
    }
    return INVALID_ITEM_ID;
}

stock GetRandomLoot()
{
    new i = random(MAX_ITEMS_ID);
    new bool:spawnPercent = RandomChance(lootData[i][E_LOOT_SPAWN_PERCENT]);
    if(!spawnPercent) return GetRandomLoot();
    else return i;
}