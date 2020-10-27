#include <utils_colour>
#include <utils_cmd>
#include <utils_vsync>
#include <utils_vehicle>
#include <utils_player>

#include <YSI_Coding\y_hooks>

hook OnGameModeInit()
{
    Logger_Log("[GAMEMODE]: utils loaded");
    return 1;
}