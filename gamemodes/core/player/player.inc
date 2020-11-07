#include <player_lastspawn>
#include <player_skin>
#include <player_packages>

#if SETUP_TABLE
    #include <player_setup-lastpos>
#endif

#include <YSI_Data\y_bit>

new 
    BitArray:PlayerSpawnState<MAX_PLAYERS>
;

hook OnPlayerConnect(playerid)
{
    Bit_Set(PlayerSpawnState, playerid, false);
    return 1;
}

hook OnPlayerSpawn(playerid)
{
    Bit_Set(PlayerSpawnState, playerid, true);
    return 1;
}

stock Player_SetSpawned(playerid, bool:status) {
    Bit_Set(PlayerSpawnState, playerid, status);
}

stock Player_IsSpawned(playerid) {
    return Bit_Get(PlayerSpawnState, playerid);
}

static ptask _PlayerPerSecondTimer[1000](playerid) {
    if(Player_IsSpawned(playerid)) {
        CallLocalFunction("OnPlayerSecondUpdate", "i", playerid);
    }
}