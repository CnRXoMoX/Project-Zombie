#include <sql-connection>

#include <YSI_Coding\y_hooks>

hook OnGameModeInit()
{
    log("[GAMEMODE]: database Loaded");
    return 1;
}