#include <a_samp>

#define YSI_YES_HEAP_MALLOC
#define YSI_NO_OPTIMISATION_MESSAGE

#define SETUP_TABLE     (true)
#define MAX_STATEMENTS  (100)
#define MYSQL_PREPARE_DEBUG (false)

#include <samp_bcrypt>
#include <a_mysql>
#include <YSI_Coding\y_inline>
#include <YSI_Coding\y_va>
#include <mysql_prepared>
#include <logger>
#include <formatex>
#include <YSI_Data\y_iterate>
#include <YSI_Coding\y_timers>
#include <streamer>

#include <constants>
#include <init>
#include <utils>
#include <database>
#include <account>
#include <player>
#include <chat>
#include <admin>
#include <user-interface>
#include <systems>

#include <mainmaps>

public OnGameModeInit()
{
    SendRconCommand("hostname "#SERVER_NAME " v" #SCRIPT_VERSION_MAJOR "." #SCRIPT_VERSION_MINOR "." #SCRIPT_VERSION_PATCH);
    SendRconCommand("gamemodetext "SERVER_MODE"");
	SendRconCommand("language "SERVER_LANGUAGE"");
    SendRconCommand("weburl "SERVER_WEBSITE"");
    Logger_Log("Test?");
    return 1;
}

public OnPlayerDisconnect(playerid, reason)
{
    return 1;
}

public OnPlayerText(playerid, text[])
{
    return 1;
}

CMD:veh(playerid, params[])
{
    new veh;
    new Float:pos[3];
    GetPlayerPos(playerid, pos[0], pos[1], pos[2]);
    veh = CreateVehicle(560, pos[0], pos[1], pos[2], 0, 0, 0, -1);
    PutPlayerInVehicle(playerid, veh, 0);
    return 1;
}

CMD:goto(playerid, params[])
{
    SetPlayerPos(playerid, 2586.707275, 2772.758544, 9.795619);
    return 1;
}

CMD:giveitem(playerid, params[])
{
    new lootName[MAX_LOOT_NAME];
    if(sscanf(params, "s[32]", lootName)) return SendSyntaxMsg(playerid, "/giveitem (item name)");
    if(strlen(lootName) > MAX_LOOT_NAME) return SendErrorMsgF(playerid, "loot name is supposed to be %d", MAX_LOOT_NAME);
    new itemID = GetItemIDFromName(lootName);
    printf("%d", itemID);
    if(!IsValidItem(itemID)) return SendErrorMsgF(playerid, "The item %s does not exist!", lootName);
    if(!PlayerHasAvailableBagSlot(playerid)) return SendErrorMsg(playerid, "You don't have any available bag slots");
    GivePlayerItem(playerid, itemID);
    return 1;
}