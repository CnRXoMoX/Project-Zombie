CMD:radio(playerid, params[])
{
    new msg[256];
    //new radio = GetItemIDFromName("Radio");
    if(sscanf(params, "s[256]", msg)) return SendSyntaxMsg(playerid, "/radio (Message)");
    //if(IsPlayerHaveItem(playerid, radio)) return SendErrorMsg(playerid, "You don't have a radio");
    SendMsgAllF(COLOR_GOLD, "[RADIO] %p (%d): "C_WHITE"%s", playerid, playerid, msg);
    return 1;
}
ALTCMD:r(radio);