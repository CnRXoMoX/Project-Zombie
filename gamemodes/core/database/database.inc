#include <sql-connection>

#include <YSI_Coding\y_hooks>

hook OnGameModeInit()
{
    Logger_Log("[GAMEMODE]: database Loaded");
    return 1;
}