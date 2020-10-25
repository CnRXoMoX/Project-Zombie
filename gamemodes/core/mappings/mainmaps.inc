#include <LV>

#include <YSI_Coding\y_hooks>

hook OnGameModeInit()
{
    Logger_Log("[GAMEMODE]: mainmaps loaded!");
    return 1;
}