#include <YSI_Coding\y_hooks>
#include <YSI_Data\y_iterate>

#define MAX_BAG_1_ITEMS         (8)
#define MAX_BAG_2_ITEMS         (16)
#define MAX_BAG_3_ITEMS         (32)
#define MAX_BAG_4_ITEMS         (64)

#define MAX_LOOT_INDEX          (15)
#define MAX_LOOT_INDEX_ITEMS    (256)
#define MAX_LOOT_INDEX_NAME     (32)
#define MAX_LOOT_SPAWN          (12683)
#define MAX_ITEMS_PER_SPAWN     (6)

#define INVALID_LOOT_ID         (-1)

enum E_LOOT_SPAWN_DATA
{
        loot_id,
Float:  loot_posX,
Float:  loot_posY,
Float:  loot_posZ,
        loot_objectHolder,
        loot_name[MAX_LOOT_INDEX_NAME]
}

static
    Iterator: gLootIter<MAX_LOOT_SPAWN>,
    loot_Data[MAX_LOOT_SPAWN][E_LOOT_SPAWN_DATA]
;

stock CreateRandomLootItem(Float:x, Float:y, Float:z)
{
    new lootDataID = GetRandomLoot();
    new lootID = Iter_Alloc(gLootIter);
    loot_Data[lootID][loot_posX] = x;
    loot_Data[lootID][loot_posY] = y;
    loot_Data[lootID][loot_posZ] = z;
    //strcat(loot_Data[lootID][loot_name], lootData[lootDataID][E_LOOT_NAME], sizeof(loot_Data[lootID][loot_name]));
    loot_Data[lootID][loot_objectHolder] = CreateDynamicObject(GetObjectIDFromID(lootDataID), x, y, z, 0, 0, 0, 0, 0);
    return lootID;
}

stock DeleteLoot(lootDataID)
{
    if(!Iter_Contains(gLootIter, lootDataID)) {
        Logger_Err("[ONDELETELOOT]: Loot Id is not found", Logger_i("LootID", lootDataID));
        return;
    }
    DestroyDynamicObject(loot_Data[lootID][loot_objectHolder]);
    loot_Data[lootDataID][loot_posX] = 0;
    loot_Data[lootDataID][loot_posY] = 0;
    loot_Data[lootDataID][loot_posZ] = 0;
    loot_Data[lootID][loot_objectHolder] = INVALID_OBJECT_ID;
    loot_name[0] = EOS;
    loot_Data[lootDataID][loot_id] = INVALID_LOOT_ID;
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