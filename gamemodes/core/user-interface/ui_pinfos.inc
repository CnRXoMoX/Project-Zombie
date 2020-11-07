#include <YSI_Coding\y_hooks>

static
    PlayerText:backPlateBox[MAX_PLAYERS],
    PlayerText:foodBox[MAX_PLAYERS],
    PlayerText:foodSprite[MAX_PLAYERS],
    PlayerText:food[MAX_PLAYERS],
    PlayerText:thirstBox[MAX_PLAYERS],
    PlayerText:thirstSprite[MAX_PLAYERS],
    PlayerText:thirst[MAX_PLAYERS],
    PlayerText:energyBox[MAX_PLAYERS],
    PlayerText:energySprite[MAX_PLAYERS],
    PlayerText:energy[MAX_PLAYERS],
    PlayerText:humanityBox[MAX_PLAYERS],
    PlayerText:humanitySprite[MAX_PLAYERS],
    PlayerText:humanity[MAX_PLAYERS];

hook OnPlayerConnect(playerid)
{    
    backPlateBox[playerid] = CreatePlayerTextDraw(playerid, 597.000000, 201.000000, "_");
    PlayerTextDrawFont(playerid, backPlateBox[playerid], 1);
    PlayerTextDrawLetterSize(playerid, backPlateBox[playerid], 0.600000, 27.550003);
    PlayerTextDrawTextSize(playerid, backPlateBox[playerid], 292.000000, 82.500000);
    PlayerTextDrawSetOutline(playerid, backPlateBox[playerid], 1);
    PlayerTextDrawSetShadow(playerid, backPlateBox[playerid], 0);
    PlayerTextDrawAlignment(playerid, backPlateBox[playerid], 2);
    PlayerTextDrawColor(playerid, backPlateBox[playerid], -1);
    PlayerTextDrawBackgroundColor(playerid, backPlateBox[playerid], 255);
    PlayerTextDrawBoxColor(playerid, backPlateBox[playerid], 255);
    PlayerTextDrawUseBox(playerid, backPlateBox[playerid], 1);
    PlayerTextDrawSetProportional(playerid, backPlateBox[playerid], 1);
    PlayerTextDrawSetSelectable(playerid, backPlateBox[playerid], 0);

    foodBox[playerid] = CreatePlayerTextDraw(playerid, 597.000000, 207.000000, "_");
    PlayerTextDrawFont(playerid, foodBox[playerid], 1);
    PlayerTextDrawLetterSize(playerid, foodBox[playerid], 0.225000, 5.499998);
    PlayerTextDrawTextSize(playerid, foodBox[playerid], 298.500000, 75.000000);
    PlayerTextDrawSetOutline(playerid, foodBox[playerid], 1);
    PlayerTextDrawSetShadow(playerid, foodBox[playerid], 0);
    PlayerTextDrawAlignment(playerid, foodBox[playerid], 2);
    PlayerTextDrawColor(playerid, foodBox[playerid], -1);
    PlayerTextDrawBackgroundColor(playerid, foodBox[playerid], 255);
    PlayerTextDrawBoxColor(playerid, foodBox[playerid], -1378294137);
    PlayerTextDrawUseBox(playerid, foodBox[playerid], 1);
    PlayerTextDrawSetProportional(playerid, foodBox[playerid], 1);
    PlayerTextDrawSetSelectable(playerid, foodBox[playerid], 0);

    foodSprite[playerid] = CreatePlayerTextDraw(playerid, 588.000000, 213.000000, "HUD:radar_burgershot");
    PlayerTextDrawFont(playerid, foodSprite[playerid], 4);
    PlayerTextDrawLetterSize(playerid, foodSprite[playerid], 0.600000, 2.000000);
    PlayerTextDrawTextSize(playerid, foodSprite[playerid], 17.000000, 17.000000);
    PlayerTextDrawSetOutline(playerid, foodSprite[playerid], 1);
    PlayerTextDrawSetShadow(playerid, foodSprite[playerid], 0);
    PlayerTextDrawAlignment(playerid, foodSprite[playerid], 1);
    PlayerTextDrawColor(playerid, foodSprite[playerid], -1);
    PlayerTextDrawBackgroundColor(playerid, foodSprite[playerid], 255);
    PlayerTextDrawBoxColor(playerid, foodSprite[playerid], 50);
    PlayerTextDrawUseBox(playerid, foodSprite[playerid], 1);
    PlayerTextDrawSetProportional(playerid, foodSprite[playerid], 1);
    PlayerTextDrawSetSelectable(playerid, foodSprite[playerid], 0);

    food[playerid] = CreatePlayerTextDraw(playerid, 597.000000, 237.000000, "500");
    PlayerTextDrawFont(playerid, food[playerid], 3);
    PlayerTextDrawLetterSize(playerid, food[playerid], 0.600000, 2.000000);
    PlayerTextDrawTextSize(playerid, food[playerid], 400.000000, 17.000000);
    PlayerTextDrawSetOutline(playerid, food[playerid], 1);
    PlayerTextDrawSetShadow(playerid, food[playerid], 0);
    PlayerTextDrawAlignment(playerid, food[playerid], 2);
    PlayerTextDrawColor(playerid, food[playerid], -1);
    PlayerTextDrawBackgroundColor(playerid, food[playerid], 255);
    PlayerTextDrawBoxColor(playerid, food[playerid], 50);
    PlayerTextDrawUseBox(playerid, food[playerid], 0);
    PlayerTextDrawSetProportional(playerid, food[playerid], 1);
    PlayerTextDrawSetSelectable(playerid, food[playerid], 0);

    thirstBox[playerid] = CreatePlayerTextDraw(playerid, 597.000000, 266.000000, "_");
    PlayerTextDrawFont(playerid, thirstBox[playerid], 1);
    PlayerTextDrawLetterSize(playerid, thirstBox[playerid], 0.225000, 5.499998);
    PlayerTextDrawTextSize(playerid, thirstBox[playerid], 298.500000, 75.000000);
    PlayerTextDrawSetOutline(playerid, thirstBox[playerid], 1);
    PlayerTextDrawSetShadow(playerid, thirstBox[playerid], 0);
    PlayerTextDrawAlignment(playerid, thirstBox[playerid], 2);
    PlayerTextDrawColor(playerid, thirstBox[playerid], -1);
    PlayerTextDrawBackgroundColor(playerid, thirstBox[playerid], 255);
    PlayerTextDrawBoxColor(playerid, thirstBox[playerid], -1378294137);
    PlayerTextDrawUseBox(playerid, thirstBox[playerid], 1);
    PlayerTextDrawSetProportional(playerid, thirstBox[playerid], 1);
    PlayerTextDrawSetSelectable(playerid, thirstBox[playerid], 0);

    thirstSprite[playerid] = CreatePlayerTextDraw(playerid, 588.000000, 273.000000, "HUD:radar_datedrink");
    PlayerTextDrawFont(playerid, thirstSprite[playerid], 4);
    PlayerTextDrawLetterSize(playerid, thirstSprite[playerid], 0.600000, 2.000000);
    PlayerTextDrawTextSize(playerid, thirstSprite[playerid], 17.000000, 17.000000);
    PlayerTextDrawSetOutline(playerid, thirstSprite[playerid], 1);
    PlayerTextDrawSetShadow(playerid, thirstSprite[playerid], 0);
    PlayerTextDrawAlignment(playerid, thirstSprite[playerid], 1);
    PlayerTextDrawColor(playerid, thirstSprite[playerid], -1);
    PlayerTextDrawBackgroundColor(playerid, thirstSprite[playerid], 255);
    PlayerTextDrawBoxColor(playerid, thirstSprite[playerid], 50);
    PlayerTextDrawUseBox(playerid, thirstSprite[playerid], 1);
    PlayerTextDrawSetProportional(playerid, thirstSprite[playerid], 1);
    PlayerTextDrawSetSelectable(playerid, thirstSprite[playerid], 0);

    thirst[playerid] = CreatePlayerTextDraw(playerid, 597.000000, 295.000000, "500");
    PlayerTextDrawFont(playerid, thirst[playerid], 3);
    PlayerTextDrawLetterSize(playerid, thirst[playerid], 0.600000, 2.000000);
    PlayerTextDrawTextSize(playerid, thirst[playerid], 400.000000, 17.000000);
    PlayerTextDrawSetOutline(playerid, thirst[playerid], 1);
    PlayerTextDrawSetShadow(playerid, thirst[playerid], 0);
    PlayerTextDrawAlignment(playerid, thirst[playerid], 2);
    PlayerTextDrawColor(playerid, thirst[playerid], -1);
    PlayerTextDrawBackgroundColor(playerid, thirst[playerid], 255);
    PlayerTextDrawBoxColor(playerid, thirst[playerid], 50);
    PlayerTextDrawUseBox(playerid, thirst[playerid], 0);
    PlayerTextDrawSetProportional(playerid, thirst[playerid], 1);
    PlayerTextDrawSetSelectable(playerid, thirst[playerid], 0);

    energyBox[playerid] = CreatePlayerTextDraw(playerid, 597.000000, 326.000000, "_");
    PlayerTextDrawFont(playerid, energyBox[playerid], 1);
    PlayerTextDrawLetterSize(playerid, energyBox[playerid], 0.225000, 5.499998);
    PlayerTextDrawTextSize(playerid, energyBox[playerid], 298.500000, 75.000000);
    PlayerTextDrawSetOutline(playerid, energyBox[playerid], 1);
    PlayerTextDrawSetShadow(playerid, energyBox[playerid], 0);
    PlayerTextDrawAlignment(playerid, energyBox[playerid], 2);
    PlayerTextDrawColor(playerid, energyBox[playerid], -1);
    PlayerTextDrawBackgroundColor(playerid, energyBox[playerid], 255);
    PlayerTextDrawBoxColor(playerid, energyBox[playerid], -1378294137);
    PlayerTextDrawUseBox(playerid, energyBox[playerid], 1);
    PlayerTextDrawSetProportional(playerid, energyBox[playerid], 1);
    PlayerTextDrawSetSelectable(playerid, energyBox[playerid], 0);

    energySprite[playerid] = CreatePlayerTextDraw(playerid, 588.000000, 333.000000, "HUD:radar_tattoo");
    PlayerTextDrawFont(playerid, energySprite[playerid], 4);
    PlayerTextDrawLetterSize(playerid, energySprite[playerid], 0.600000, 2.000000);
    PlayerTextDrawTextSize(playerid, energySprite[playerid], 17.000000, 17.000000);
    PlayerTextDrawSetOutline(playerid, energySprite[playerid], 1);
    PlayerTextDrawSetShadow(playerid, energySprite[playerid], 0);
    PlayerTextDrawAlignment(playerid, energySprite[playerid], 1);
    PlayerTextDrawColor(playerid, energySprite[playerid], -1);
    PlayerTextDrawBackgroundColor(playerid, energySprite[playerid], 255);
    PlayerTextDrawBoxColor(playerid, energySprite[playerid], 50);
    PlayerTextDrawUseBox(playerid, energySprite[playerid], 1);
    PlayerTextDrawSetProportional(playerid, energySprite[playerid], 1);
    PlayerTextDrawSetSelectable(playerid, energySprite[playerid], 0);

    energy[playerid] = CreatePlayerTextDraw(playerid, 597.000000, 354.000000, "500");
    PlayerTextDrawFont(playerid, energy[playerid], 3);
    PlayerTextDrawLetterSize(playerid, energy[playerid], 0.600000, 2.000000);
    PlayerTextDrawTextSize(playerid, energy[playerid], 400.000000, 17.000000);
    PlayerTextDrawSetOutline(playerid, energy[playerid], 1);
    PlayerTextDrawSetShadow(playerid, energy[playerid], 0);
    PlayerTextDrawAlignment(playerid, energy[playerid], 2);
    PlayerTextDrawColor(playerid, energy[playerid], -1);
    PlayerTextDrawBackgroundColor(playerid, energy[playerid], 255);
    PlayerTextDrawBoxColor(playerid, energy[playerid], 50);
    PlayerTextDrawUseBox(playerid, energy[playerid], 0);
    PlayerTextDrawSetProportional(playerid, energy[playerid], 1);
    PlayerTextDrawSetSelectable(playerid, energy[playerid], 0);

    humanityBox[playerid] = CreatePlayerTextDraw(playerid, 597.000000, 386.000000, "_");
    PlayerTextDrawFont(playerid, humanityBox[playerid], 1);
    PlayerTextDrawLetterSize(playerid, humanityBox[playerid], 0.225000, 5.499998);
    PlayerTextDrawTextSize(playerid, humanityBox[playerid], 298.500000, 75.000000);
    PlayerTextDrawSetOutline(playerid, humanityBox[playerid], 1);
    PlayerTextDrawSetShadow(playerid, humanityBox[playerid], 0);
    PlayerTextDrawAlignment(playerid, humanityBox[playerid], 2);
    PlayerTextDrawColor(playerid, humanityBox[playerid], -1);
    PlayerTextDrawBackgroundColor(playerid, humanityBox[playerid], 255);
    PlayerTextDrawBoxColor(playerid, humanityBox[playerid], -1378294137);
    PlayerTextDrawUseBox(playerid, humanityBox[playerid], 1);
    PlayerTextDrawSetProportional(playerid, humanityBox[playerid], 1);
    PlayerTextDrawSetSelectable(playerid, humanityBox[playerid], 0);

    humanitySprite[playerid] = CreatePlayerTextDraw(playerid, 588.000000, 391.000000, "HUD:radar_locosyndicate");
    PlayerTextDrawFont(playerid, humanitySprite[playerid], 4);
    PlayerTextDrawLetterSize(playerid, humanitySprite[playerid], 0.600000, 2.000000);
    PlayerTextDrawTextSize(playerid, humanitySprite[playerid], 17.000000, 17.000000);
    PlayerTextDrawSetOutline(playerid, humanitySprite[playerid], 1);
    PlayerTextDrawSetShadow(playerid, humanitySprite[playerid], 0);
    PlayerTextDrawAlignment(playerid, humanitySprite[playerid], 1);
    PlayerTextDrawColor(playerid, humanitySprite[playerid], -1);
    PlayerTextDrawBackgroundColor(playerid, humanitySprite[playerid], 255);
    PlayerTextDrawBoxColor(playerid, humanitySprite[playerid], 50);
    PlayerTextDrawUseBox(playerid, humanitySprite[playerid], 1);
    PlayerTextDrawSetProportional(playerid, humanitySprite[playerid], 1);
    PlayerTextDrawSetSelectable(playerid, humanitySprite[playerid], 0);

    humanity[playerid] = CreatePlayerTextDraw(playerid, 597.000000, 413.000000, "500");
    PlayerTextDrawFont(playerid, humanity[playerid], 3);
    PlayerTextDrawLetterSize(playerid, humanity[playerid], 0.600000, 2.000000);
    PlayerTextDrawTextSize(playerid, humanity[playerid], 400.000000, 17.000000);
    PlayerTextDrawSetOutline(playerid, humanity[playerid], 1);
    PlayerTextDrawSetShadow(playerid, humanity[playerid], 0);
    PlayerTextDrawAlignment(playerid, humanity[playerid], 2);
    PlayerTextDrawColor(playerid, humanity[playerid], -1);
    PlayerTextDrawBackgroundColor(playerid, humanity[playerid], 255);
    PlayerTextDrawBoxColor(playerid, humanity[playerid], 50);
    PlayerTextDrawUseBox(playerid, humanity[playerid], 0);
    PlayerTextDrawSetProportional(playerid, humanity[playerid], 1);
    PlayerTextDrawSetSelectable(playerid, humanity[playerid], 0);
}

hook OnPlayerSpawn(playerid)
{
    PlayerTextDrawShow(playerid, backPlateBox[playerid]);
    PlayerTextDrawShow(playerid, foodBox[playerid]);
    PlayerTextDrawShow(playerid, foodSprite[playerid]);
    PlayerTextDrawShow(playerid, food[playerid]);
    PlayerTextDrawShow(playerid, thirstBox[playerid]);
    PlayerTextDrawShow(playerid, thirstSprite[playerid]);
    PlayerTextDrawShow(playerid, thirst[playerid]);
    PlayerTextDrawShow(playerid, energyBox[playerid]);
    PlayerTextDrawShow(playerid, energySprite[playerid]);
    PlayerTextDrawShow(playerid, energy[playerid]);
    PlayerTextDrawShow(playerid, humanityBox[playerid]);
    PlayerTextDrawShow(playerid, humanitySprite[playerid]);
    PlayerTextDrawShow(playerid, humanity[playerid]);
    return 1;
}

hook OnPlayerSecondUpdate(playerid)
{
    new foodStm[128];
    new foodInt = floatToInteger(GetPlayerFood(playerid));
    format(foodStm, sizeof(foodStm), "%d", foodInt);
    PlayerTextDrawSetString(playerid, food[playerid], foodStm);

    new thirstStm[128];
    new thirstInt = floatToInteger(GetPlayerThirst(playerid));
    format(thirstStm, sizeof(thirstStm), "%d", thirstInt);
    PlayerTextDrawSetString(playerid, thirst[playerid], thirstStm);
    return 1;
}