#include <YSI_Coding\y_hooks>
#include <YSI_Data\y_iterate>

#define MAX_LOOT_INDEX          (15)
#define MAX_LOOT_INDEX_ITEMS    (256)
#define MAX_LOOT_INDEX_NAME     (32)
#define MAX_LOOT_SPAWN          (12683)
#define MAX_ITEMS_PER_SPAWN     (6)

#define INVALID_LOOT_ID         (-1)

enum E_LOOT_SPAWN_DATA
{
        loot_id,
        loot_itemID,
Float:  loot_posX,
Float:  loot_posY,
Float:  loot_posZ,
        loot_objectHolder,
        loot_name[MAX_LOOT_INDEX_NAME],
bool:   loot_pickupable
}

new
    Iterator: gLootIter<MAX_LOOT_SPAWN>
;

new
    loot_Data[MAX_LOOT_SPAWN][E_LOOT_SPAWN_DATA]
;

stock bool:IsItemPickupable(lootid) {
    if(loot_Data[lootid][loot_pickupable]) {
        return true;
    }
    return false;
}

stock CreateRandomLootItem(Float:x, Float:y, Float:z)
{
    new lootDataID = GetRandomLoot();
    new lootID = Iter_Alloc(gLootIter);
    loot_Data[lootID][loot_id] = lootID;
    loot_Data[lootID][loot_posX] = x;
    loot_Data[lootID][loot_posY] = y;
    loot_Data[lootID][loot_posZ] = z;
    loot_Data[lootID][loot_pickupable] = true;
    loot_Data[lootID][loot_itemID] = lootDataID;
    strcpy(loot_Data[lootID][loot_name], lootData[lootDataID][E_LOOT_NAME]);
    loot_Data[lootID][loot_objectHolder] = CreateDynamicObject(GetObjectIDFromID(lootDataID), x, y, z, 0, 0, 0, 0, 0);
    return lootID;
}

stock AddStaticLootItem(iId, Float:x, Float:y, Float:z)
{
    new lootID = Iter_Alloc(gLootIter);
    loot_Data[lootID][loot_id] = lootID;
    loot_Data[lootID][loot_posX] = x;
    loot_Data[lootID][loot_posY] = y;
    loot_Data[lootID][loot_posZ] = z;
    loot_Data[lootID][loot_pickupable] = true;
    loot_Data[lootID][loot_itemID] = iId;
    strcpy(loot_Data[lootID][loot_name], lootData[iId][E_LOOT_NAME]);
    loot_Data[lootID][loot_objectHolder] = CreateDynamicObject(GetObjectIDFromID(iId), x, y, z, 0, 0, 0, 0, 0);
    return lootID;
}

stock DeleteLoot(lootDataID)
{
    if(!Iter_Contains(gLootIter, lootDataID)) {
        Logger_Err("[ONDELETELOOT]: Loot Id is not found", Logger_I("LootID", lootDataID));
        return 1;
    }
    DestroyDynamicObject(loot_Data[lootDataID][loot_objectHolder]);
    loot_Data[lootDataID][loot_posX] = 0;
    loot_Data[lootDataID][loot_posY] = 0;
    loot_Data[lootDataID][loot_posZ] = 0;
    loot_Data[lootDataID][loot_objectHolder] = INVALID_OBJECT_ID;
    loot_Data[lootDataID][loot_name][0] = EOS;
    loot_Data[lootDataID][loot_id] = INVALID_LOOT_ID;
    loot_Data[lootDataID][loot_pickupable] = false;
    Iter_Remove(gLootIter, lootDataID);
    return 1;
}

stock GetLootSpawn(selectedLootID, &Float:x, &Float:y, &Float:z)
{
    x = loot_Data[selectedLootID][loot_posX];
    y = loot_Data[selectedLootID][loot_posY];
    z = loot_Data[selectedLootID][loot_posZ];
    return 1;
}