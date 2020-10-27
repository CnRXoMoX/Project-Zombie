#include <YSI_Coding\y_hooks>

#define MAX_BAG_1_ITEMS         (8)
#define MAX_BAG_2_ITEMS         (16)
#define MAX_BAG_3_ITEMS         (32)
#define MAX_BAG_4_ITEMS         (64)

static
    gPlayerBagLvl[MAX_PLAYERS],
    gPlayerBagSlots[MAX_PLAYERS]
;

stock GetBagSlots(lvl) {
    new baglevel;
    switch(lvl) {
        case 1: baglevel = MAX_BAG_1_ITEMS;
        case 2: baglevel = MAX_BAG_2_ITEMS;
        case 3: baglevel = MAX_BAG_3_ITEMS;
        case 4: baglevel = MAX_BAG_4_ITEMS;
        default: baglevel = MAX_BAG_1_ITEMS;
    }
    return baglevel;
}

stock GivePlayerBag(playerid, lvl) {
    gPlayerBagLvl[playerid] = lvl;
    gPlayerBagSlots[playerid] = GetBagSlots(lvl);
}

stock Player_GetBagSlots(playerid) return gPlayerBagSlots[playerid];
stock Player_GetBagLevel(playerid) return gPlayerBagLvl[playerid];

hook OnPlayerUpdate(playerid)
{
    if(gPlayerBagSlots[playerid] != GetBagSlots(gPlayerBagLvl[playerid])) {
        // Anti bug i guess? but we need to investigate tho xd
        GivePlayerBag(playerid, gPlayerBagLvl[playerid]);
    }
    return 1;
}