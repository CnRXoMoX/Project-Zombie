#include <chat_message>

#include <YSI_Coding\y_hooks>

public OnPlayerText(playerid, text[])
{
    foreach(new i : Player)
    {
        new Float:x, Float:y, Float:z;
        GetPlayerPos(playerid, x, y, z);
        if(IsPlayerInRangeOfPoint(i, 7.0, x, y, z))
        {
            SendMsgF(i, COLOR_WHITE, "%p (%d): %s", playerid, playerid, text);
        }
    }
    return 0;
}