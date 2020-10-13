#include <utils_colour>
#include <utils_cmd>
#include <utils_vsync>
#include <utils_vehicle>
#include <utils_player>

#include <YSI_Coding\y_hooks>

stock LOGGER_FIELD:_p(const field[], playerid) {
    new result[MAX_FIELD_NAME + 1 + MAX_FIELD_VALUE];
    formatex(result, sizeof(result), "%s=\"%p\"", field, playerid);
    return LOGGER_FIELD:result;
}

hook OnGameModeInit()
{
    log("[GAMEMODE]: utils loaded");
    return 1;
}