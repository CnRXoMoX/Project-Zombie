#define SERVER_NAME "DayZ Survival"
#define SCRIPT_VERSION_MAJOR "1"
#define SCRIPT_VERSION_MINOR "0"
#define SCRIPT_VERSION_PATCH "0"
#define SERVER_MODE "DayZ/Survival/Scavage"
#define SERVER_LANGUAGE "English"
#define SERVER_WEBSITE "discord.gg/samp"

main() {
    log("gamemode initialised.");
	logger_debug(PLAYER_DEBUG_HANDLER, true);
}