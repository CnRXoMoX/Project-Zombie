#include <YSI_Coding\y_hooks>

static
    PlayerText:mapBoxHider[MAX_PLAYERS],
    PlayerText:textMessage[MAX_PLAYERS]
;

hook OnPlayerConnect(playerid)
{    
    mapBoxHider[playerid] = CreatePlayerTextDraw(playerid, 70.000000, 329.000000, "_");
    PlayerTextDrawFont(playerid, mapBoxHider[playerid], 1);
    PlayerTextDrawLetterSize(playerid, mapBoxHider[playerid], 0.600000, 11.150006);
    PlayerTextDrawTextSize(playerid, mapBoxHider[playerid], 302.000000, 88.000000);
    PlayerTextDrawSetOutline(playerid, mapBoxHider[playerid], 1);
    PlayerTextDrawSetShadow(playerid, mapBoxHider[playerid], 0);
    PlayerTextDrawAlignment(playerid, mapBoxHider[playerid], 2);
    PlayerTextDrawColor(playerid, mapBoxHider[playerid], -1);
    PlayerTextDrawBackgroundColor(playerid, mapBoxHider[playerid], 255);
    PlayerTextDrawBoxColor(playerid, mapBoxHider[playerid], 255);
    PlayerTextDrawUseBox(playerid, mapBoxHider[playerid], 1);
    PlayerTextDrawSetProportional(playerid, mapBoxHider[playerid], 1);
    PlayerTextDrawSetSelectable(playerid, mapBoxHider[playerid], 0);

    textMessage[playerid] = CreatePlayerTextDraw(playerid, 69.000000, 351.000000, "~r~You~n~Need~n~GPS");
    PlayerTextDrawFont(playerid, textMessage[playerid], 1);
    PlayerTextDrawLetterSize(playerid, textMessage[playerid], 0.600000, 2.000000);
    PlayerTextDrawTextSize(playerid, textMessage[playerid], 400.000000, 17.000000);
    PlayerTextDrawSetOutline(playerid, textMessage[playerid], 2);
    PlayerTextDrawSetShadow(playerid, textMessage[playerid], 1);
    PlayerTextDrawAlignment(playerid, textMessage[playerid], 2);
    PlayerTextDrawColor(playerid, textMessage[playerid], -1);
    PlayerTextDrawBackgroundColor(playerid, textMessage[playerid], 255);
    PlayerTextDrawBoxColor(playerid, textMessage[playerid], 50);
    PlayerTextDrawUseBox(playerid, textMessage[playerid], 0);
    PlayerTextDrawSetProportional(playerid, textMessage[playerid], 1);
    PlayerTextDrawSetSelectable(playerid, textMessage[playerid], 0);
    return 1;
}

hook OnPlayerSpawn(playerid)
{
    repeat playerUpdateGPS(playerid);
    return 1;
}

timer playerUpdateGPS[1000](playerid)
{
    new itemID = GetItemIDFromName("GPS");
    if(!IsPlayerHaveItem(playerid, itemID)) {
        PlayerTextDrawShow(playerid, mapBoxHider[playerid]);
        PlayerTextDrawShow(playerid, textMessage[playerid]);
    } else {
        PlayerTextDrawHide(playerid, mapBoxHider[playerid]);
        PlayerTextDrawHide(playerid, textMessage[playerid]);
    }
    return 1;
}