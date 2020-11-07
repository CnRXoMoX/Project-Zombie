#include <YSI_Coding\y_hooks>

Player_NormalPackage(playerid) {
    GivePlayerItem(playerid, 1);
    GivePlayerItem(playerid, 5);
    GivePlayerItem(playerid, 0);
    SetPlayerFood(playerid, 100);
    SetPlayerThirst(playerid, 100);
    return 1;
}

hook OnPlayerSpawn(playerid)
{
    if(Player_New(playerid) || IsPlayerJustDied(playerid)) {
        Player_NormalPackage(playerid);
    }
    return 1;
}