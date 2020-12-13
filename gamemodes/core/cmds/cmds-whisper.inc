CMD:whisper(playerid, params[])
{
    new msg[256];
    if(sscanf(params, "s[256]", msg)) return SendSyntaxMsg(playerid, "/w (message)");
    foreach(new i : Player)
    {
        new Float:x, Float:y, Float:z;
        GetPlayerPos(playerid, x, y, z);
        if(IsPlayerInRangeOfPoint(i, 4.0, x, y, z))
        {
            SendMsgF(i, COLOR_WHITE, "(WHISPER) %p (%d): %s", playerid, playerid, msg);
        }
    }
    return 1;
}
ALTCMD:w(whisper);