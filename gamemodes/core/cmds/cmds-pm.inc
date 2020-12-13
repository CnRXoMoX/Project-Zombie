CMD:pm(playerid, params[])
{
    new targetid, msg[256];
    if(sscanf(params, "us[256]", targetid, msg)) return SendSyntaxMsg(playerid, "/pm (name/id) (message)");
    if(!IsPlayerConnected(targetid)) return SendErrorMsg(playerid, ERROR_PLAYER_NOT_CONNECTED);
    SendMsgF(targetid, COLOR_YELLOW, "[FROM] %p (%d): %s", playerid, playerid, msg);
    SendMsgF(playerid, COLOR_YELLOW, "[TO] %p (%d): %s", targetid, targetid, msg);
    return 1;
}