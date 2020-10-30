#include <YSI_Coding\y_hooks>

static 
    PlayerText:PlayerNameTD[MAX_PLAYERS],
    PlayerText:PlayerTD[MAX_PLAYERS][4],
    PlayerText:RelootTD[MAX_PLAYERS],
    PlayerText:formainui[MAX_PLAYERS],
    PlayerText:weaponHolder[MAX_PLAYERS],
    PlayerText:uppermainui[MAX_PLAYERS],
    PlayerText:header[MAX_PLAYERS],
    PlayerText:seperator[MAX_PLAYERS],
    PlayerText:timeAlive[MAX_PLAYERS],
    PlayerText:aliveTimeTimer[MAX_PLAYERS],
    PlayerText:zombiesKilled[MAX_PLAYERS],
    PlayerText:zombiesKilledCounter[MAX_PLAYERS]
;

hook OnPlayerConnect(playerid)
{    
    PlayerNameTD[playerid] = CreatePlayerTextDraw(playerid, 554.000000, 20.000000, "XomoX_Test");
    PlayerTextDrawFont(playerid, PlayerNameTD[playerid], 1);
    PlayerTextDrawLetterSize(playerid, PlayerNameTD[playerid], 0.320833, 1.500000);
    PlayerTextDrawTextSize(playerid, PlayerNameTD[playerid], 400.000000, 17.000000);
    PlayerTextDrawSetOutline(playerid, PlayerNameTD[playerid], 1);
    PlayerTextDrawSetShadow(playerid, PlayerNameTD[playerid], 0);
    PlayerTextDrawAlignment(playerid, PlayerNameTD[playerid], 2);
    PlayerTextDrawColor(playerid, PlayerNameTD[playerid], -1);
    PlayerTextDrawBackgroundColor(playerid, PlayerNameTD[playerid], 255);
    PlayerTextDrawBoxColor(playerid, PlayerNameTD[playerid], 50);
    PlayerTextDrawUseBox(playerid, PlayerNameTD[playerid], 0);
    PlayerTextDrawSetProportional(playerid, PlayerNameTD[playerid], 1);
    PlayerTextDrawSetSelectable(playerid, PlayerNameTD[playerid], 0);

    formainui[playerid] = CreatePlayerTextDraw(playerid, 554.000000, 18.000000, "_");
    PlayerTextDrawFont(playerid, formainui[playerid], 1);
    PlayerTextDrawLetterSize(playerid, formainui[playerid], 0.583333, 14.350015);
    PlayerTextDrawTextSize(playerid, formainui[playerid], 304.000000, 152.500000);
    PlayerTextDrawSetOutline(playerid, formainui[playerid], 0);
    PlayerTextDrawSetShadow(playerid, formainui[playerid], 0);
    PlayerTextDrawAlignment(playerid, formainui[playerid], 2);
    PlayerTextDrawColor(playerid, formainui[playerid], -1);
    PlayerTextDrawBackgroundColor(playerid, formainui[playerid], 255);
    PlayerTextDrawBoxColor(playerid, formainui[playerid], 255);
    PlayerTextDrawUseBox(playerid, formainui[playerid], 1);
    PlayerTextDrawSetProportional(playerid, formainui[playerid], 1);
    PlayerTextDrawSetSelectable(playerid, formainui[playerid], 0);

    uppermainui[playerid] = CreatePlayerTextDraw(playerid, 554.000000, 23.000000, "_");
    PlayerTextDrawFont(playerid, uppermainui[playerid], 1);
    PlayerTextDrawLetterSize(playerid, uppermainui[playerid], 0.600000, 13.100010);
    PlayerTextDrawTextSize(playerid, uppermainui[playerid], 362.500000, 142.500000);
    PlayerTextDrawSetOutline(playerid, uppermainui[playerid], 1);
    PlayerTextDrawSetShadow(playerid, uppermainui[playerid], 0);
    PlayerTextDrawAlignment(playerid, uppermainui[playerid], 2);
    PlayerTextDrawColor(playerid, uppermainui[playerid], -1);
    PlayerTextDrawBackgroundColor(playerid, uppermainui[playerid], 255);
    PlayerTextDrawBoxColor(playerid, uppermainui[playerid], -168436601);
    PlayerTextDrawUseBox(playerid, uppermainui[playerid], 1);
    PlayerTextDrawSetProportional(playerid, uppermainui[playerid], 1);
    PlayerTextDrawSetSelectable(playerid, uppermainui[playerid], 0);

    header[playerid] = CreatePlayerTextDraw(playerid, 551.000000, 2.000000, "discord.gg/samp");
    PlayerTextDrawFont(playerid, header[playerid], 1);
    PlayerTextDrawLetterSize(playerid, header[playerid], 0.295832, 1.200000);
    PlayerTextDrawTextSize(playerid, header[playerid], 400.000000, 17.000000);
    PlayerTextDrawSetOutline(playerid, header[playerid], 1);
    PlayerTextDrawSetShadow(playerid, header[playerid], 0);
    PlayerTextDrawAlignment(playerid, header[playerid], 1);
    PlayerTextDrawColor(playerid, header[playerid], -1);
    PlayerTextDrawBackgroundColor(playerid, header[playerid], 255);
    PlayerTextDrawBoxColor(playerid, header[playerid], 50);
    PlayerTextDrawUseBox(playerid, header[playerid], 0);
    PlayerTextDrawSetProportional(playerid, header[playerid], 1);
    PlayerTextDrawSetSelectable(playerid, header[playerid], 0);

    seperator[playerid] = CreatePlayerTextDraw(playerid, 554.000000, 33.000000, "-------------------------------");
    PlayerTextDrawFont(playerid, seperator[playerid], 1);
    PlayerTextDrawLetterSize(playerid, seperator[playerid], 0.295832, 0.550000);
    PlayerTextDrawTextSize(playerid, seperator[playerid], 400.000000, 17.000000);
    PlayerTextDrawSetOutline(playerid, seperator[playerid], 1);
    PlayerTextDrawSetShadow(playerid, seperator[playerid], 0);
    PlayerTextDrawAlignment(playerid, seperator[playerid], 2);
    PlayerTextDrawColor(playerid, seperator[playerid], -1);
    PlayerTextDrawBackgroundColor(playerid, seperator[playerid], 255);
    PlayerTextDrawBoxColor(playerid, seperator[playerid], 50);
    PlayerTextDrawUseBox(playerid, seperator[playerid], 0);
    PlayerTextDrawSetProportional(playerid, seperator[playerid], 1);
    PlayerTextDrawSetSelectable(playerid, seperator[playerid], 0);

    timeAlive[playerid] = CreatePlayerTextDraw(playerid, 535.000000, 39.000000, "Time Alive:");
    PlayerTextDrawFont(playerid, timeAlive[playerid], 1);
    PlayerTextDrawLetterSize(playerid, timeAlive[playerid], 0.258332, 1.199998);
    PlayerTextDrawTextSize(playerid, timeAlive[playerid], 400.000000, 17.000000);
    PlayerTextDrawSetOutline(playerid, timeAlive[playerid], 1);
    PlayerTextDrawSetShadow(playerid, timeAlive[playerid], 0);
    PlayerTextDrawAlignment(playerid, timeAlive[playerid], 3);
    PlayerTextDrawColor(playerid, timeAlive[playerid], -1);
    PlayerTextDrawBackgroundColor(playerid, timeAlive[playerid], 255);
    PlayerTextDrawBoxColor(playerid, timeAlive[playerid], 50);
    PlayerTextDrawUseBox(playerid, timeAlive[playerid], 0);
    PlayerTextDrawSetProportional(playerid, timeAlive[playerid], 1);
    PlayerTextDrawSetSelectable(playerid, timeAlive[playerid], 0);

    aliveTimeTimer[playerid] = CreatePlayerTextDraw(playerid, 569.000000, 39.000000, "00:00:00");
    PlayerTextDrawFont(playerid, aliveTimeTimer[playerid], 1);
    PlayerTextDrawLetterSize(playerid, aliveTimeTimer[playerid], 0.304165, 1.199000);
    PlayerTextDrawTextSize(playerid, aliveTimeTimer[playerid], 400.000000, 17.000000);
    PlayerTextDrawSetOutline(playerid, aliveTimeTimer[playerid], 1);
    PlayerTextDrawSetShadow(playerid, aliveTimeTimer[playerid], 0);
    PlayerTextDrawAlignment(playerid, aliveTimeTimer[playerid], 1);
    PlayerTextDrawColor(playerid, aliveTimeTimer[playerid], -1);
    PlayerTextDrawBackgroundColor(playerid, aliveTimeTimer[playerid], 255);
    PlayerTextDrawBoxColor(playerid, aliveTimeTimer[playerid], 50);
    PlayerTextDrawUseBox(playerid, aliveTimeTimer[playerid], 0);
    PlayerTextDrawSetProportional(playerid, aliveTimeTimer[playerid], 1);
    PlayerTextDrawSetSelectable(playerid, aliveTimeTimer[playerid], 0);

    zombiesKilled[playerid] = CreatePlayerTextDraw(playerid, 542.000000, 52.000000, "Zombies Killed:");
    PlayerTextDrawFont(playerid, zombiesKilled[playerid], 1);
    PlayerTextDrawLetterSize(playerid, zombiesKilled[playerid], 0.224665, 1.199000);
    PlayerTextDrawTextSize(playerid, zombiesKilled[playerid], 400.000000, 17.000000);
    PlayerTextDrawSetOutline(playerid, zombiesKilled[playerid], 1);
    PlayerTextDrawSetShadow(playerid, zombiesKilled[playerid], 0);
    PlayerTextDrawAlignment(playerid, zombiesKilled[playerid], 3);
    PlayerTextDrawColor(playerid, zombiesKilled[playerid], -1);
    PlayerTextDrawBackgroundColor(playerid, zombiesKilled[playerid], 255);
    PlayerTextDrawBoxColor(playerid, zombiesKilled[playerid], 50);
    PlayerTextDrawUseBox(playerid, zombiesKilled[playerid], 0);
    PlayerTextDrawSetProportional(playerid, zombiesKilled[playerid], 1);
    PlayerTextDrawSetSelectable(playerid, zombiesKilled[playerid], 0);

    zombiesKilledCounter[playerid] = CreatePlayerTextDraw(playerid, 583.000000, 51.000000, "100");
    PlayerTextDrawFont(playerid, zombiesKilledCounter[playerid], 1);
    PlayerTextDrawLetterSize(playerid, zombiesKilledCounter[playerid], 0.303999, 1.199000);
    PlayerTextDrawTextSize(playerid, zombiesKilledCounter[playerid], 400.000000, 17.000000);
    PlayerTextDrawSetOutline(playerid, zombiesKilledCounter[playerid], 1);
    PlayerTextDrawSetShadow(playerid, zombiesKilledCounter[playerid], 0);
    PlayerTextDrawAlignment(playerid, zombiesKilledCounter[playerid], 1);
    PlayerTextDrawColor(playerid, zombiesKilledCounter[playerid], -1);
    PlayerTextDrawBackgroundColor(playerid, zombiesKilledCounter[playerid], 255);
    PlayerTextDrawBoxColor(playerid, zombiesKilledCounter[playerid], 50);
    PlayerTextDrawUseBox(playerid, zombiesKilledCounter[playerid], 0);
    PlayerTextDrawSetProportional(playerid, zombiesKilledCounter[playerid], 1);
    PlayerTextDrawSetSelectable(playerid, zombiesKilledCounter[playerid], 0);

    PlayerTD[playerid][0] = CreatePlayerTextDraw(playerid, 518.000000, 64.000000, "Murders:");
    PlayerTextDrawFont(playerid, PlayerTD[playerid][0], 1);
    PlayerTextDrawLetterSize(playerid, PlayerTD[playerid][0], 0.224665, 1.199000);
    PlayerTextDrawTextSize(playerid, PlayerTD[playerid][0], 400.000000, 17.000000);
    PlayerTextDrawSetOutline(playerid, PlayerTD[playerid][0], 1);
    PlayerTextDrawSetShadow(playerid, PlayerTD[playerid][0], 0);
    PlayerTextDrawAlignment(playerid, PlayerTD[playerid][0], 3);
    PlayerTextDrawColor(playerid, PlayerTD[playerid][0], -1);
    PlayerTextDrawBackgroundColor(playerid, PlayerTD[playerid][0], 255);
    PlayerTextDrawBoxColor(playerid, PlayerTD[playerid][0], 50);
    PlayerTextDrawUseBox(playerid, PlayerTD[playerid][0], 0);
    PlayerTextDrawSetProportional(playerid, PlayerTD[playerid][0], 1);
    PlayerTextDrawSetSelectable(playerid, PlayerTD[playerid][0], 0);

    PlayerTD[playerid][1] = CreatePlayerTextDraw(playerid, 583.000000, 64.000000, "100");
    PlayerTextDrawFont(playerid, PlayerTD[playerid][1], 1);
    PlayerTextDrawLetterSize(playerid, PlayerTD[playerid][1], 0.303999, 1.199000);
    PlayerTextDrawTextSize(playerid, PlayerTD[playerid][1], 400.000000, 17.000000);
    PlayerTextDrawSetOutline(playerid, PlayerTD[playerid][1], 1);
    PlayerTextDrawSetShadow(playerid, PlayerTD[playerid][1], 0);
    PlayerTextDrawAlignment(playerid, PlayerTD[playerid][1], 1);
    PlayerTextDrawColor(playerid, PlayerTD[playerid][1], -1);
    PlayerTextDrawBackgroundColor(playerid, PlayerTD[playerid][1], 255);
    PlayerTextDrawBoxColor(playerid, PlayerTD[playerid][1], 50);
    PlayerTextDrawUseBox(playerid, PlayerTD[playerid][1], 0);
    PlayerTextDrawSetProportional(playerid, PlayerTD[playerid][1], 1);
    PlayerTextDrawSetSelectable(playerid, PlayerTD[playerid][1], 0);

    PlayerTD[playerid][2] = CreatePlayerTextDraw(playerid, 554.000000, 124.000000, "-------------------------------");
    PlayerTextDrawFont(playerid, PlayerTD[playerid][2], 1);
    PlayerTextDrawLetterSize(playerid, PlayerTD[playerid][2], 0.295832, 0.550000);
    PlayerTextDrawTextSize(playerid, PlayerTD[playerid][2], 400.000000, 17.000000);
    PlayerTextDrawSetOutline(playerid, PlayerTD[playerid][2], 1);
    PlayerTextDrawSetShadow(playerid, PlayerTD[playerid][2], 0);
    PlayerTextDrawAlignment(playerid, PlayerTD[playerid][2], 2);
    PlayerTextDrawColor(playerid, PlayerTD[playerid][2], -1);
    PlayerTextDrawBackgroundColor(playerid, PlayerTD[playerid][2], 255);
    PlayerTextDrawBoxColor(playerid, PlayerTD[playerid][2], 50);
    PlayerTextDrawUseBox(playerid, PlayerTD[playerid][2], 0);
    PlayerTextDrawSetProportional(playerid, PlayerTD[playerid][2], 1);
    PlayerTextDrawSetSelectable(playerid, PlayerTD[playerid][2], 0);

    RelootTD[playerid] = CreatePlayerTextDraw(playerid, 140.000000, 376.000000, "Reloot:~n~~g~00:00");
    PlayerTextDrawFont(playerid, RelootTD[playerid], 1);
    PlayerTextDrawLetterSize(playerid, RelootTD[playerid], 0.266665, 1.500000);
    PlayerTextDrawTextSize(playerid, RelootTD[playerid], 400.000000, 17.000000);
    PlayerTextDrawSetOutline(playerid, RelootTD[playerid], 1);
    PlayerTextDrawSetShadow(playerid, RelootTD[playerid], 0);
    PlayerTextDrawAlignment(playerid, RelootTD[playerid], 1);
    PlayerTextDrawColor(playerid, RelootTD[playerid], -1);
    PlayerTextDrawBackgroundColor(playerid, RelootTD[playerid], 255);
    PlayerTextDrawBoxColor(playerid, RelootTD[playerid], 50);
    PlayerTextDrawUseBox(playerid, RelootTD[playerid], 0);
    PlayerTextDrawSetProportional(playerid, RelootTD[playerid], 1);
    PlayerTextDrawSetSelectable(playerid, RelootTD[playerid], 0);

    weaponHolder[playerid] = CreatePlayerTextDraw(playerid, 608.000000, 128.000000, "Weapon: M4 - 300");
    PlayerTextDrawFont(playerid, weaponHolder[playerid], 1);
    PlayerTextDrawLetterSize(playerid, weaponHolder[playerid], 0.350000, 1.500000);
    PlayerTextDrawTextSize(playerid, weaponHolder[playerid], 400.000000, 17.000000);
    PlayerTextDrawSetOutline(playerid, weaponHolder[playerid], 1);
    PlayerTextDrawSetShadow(playerid, weaponHolder[playerid], 0);
    PlayerTextDrawAlignment(playerid, weaponHolder[playerid], 3);
    PlayerTextDrawColor(playerid, weaponHolder[playerid], -1);
    PlayerTextDrawBackgroundColor(playerid, weaponHolder[playerid], 255);
    PlayerTextDrawBoxColor(playerid, weaponHolder[playerid], 50);
    PlayerTextDrawUseBox(playerid, weaponHolder[playerid], 0);
    PlayerTextDrawSetProportional(playerid, weaponHolder[playerid], 1);
    PlayerTextDrawSetSelectable(playerid, weaponHolder[playerid], 0);
    return 1;
}

static
    timeLeftCounter[MAX_PLAYERS],
    playerHoursPlayed[MAX_PLAYERS],
    Timer:timeLeftTimer[MAX_PLAYERS]
;

static
    Statement: stmt_intertPlayTime,
    Statement: stmt_loadPlayTime,
    Statement: stmt_updatePlayTime
;

hook OnMySQLConnected()
{
    static const insertQuery[] = " \
    INSERT INTO players_alivetime (u_id) \
    VALUES (?) \
    ";
    stmt_intertPlayTime = MySQL_PrepareStatement(MySQL_GetHandle(), insertQuery);

    static const loadQuery[] = " \
    SELECT \
        seconds, \
        hours \
    FROM \
        players_alivetime \
    WHERE \
        u_id = ? \
    ";
    stmt_loadPlayTime = MySQL_PrepareStatement(MySQL_GetHandle(), loadQuery);

    static const updateQuery[] = "\
    UPDATE \
        players_alivetime \
    SET \
        seconds = ?, \
        hours = ? \
    WHERE \
        u_id = ? \
    ";
    stmt_updatePlayTime = MySQL_PrepareStatement(MySQL_GetHandle(), updateQuery);
}

hook OnPlayerRegister(playerid)
{
    MySQL_BindInt(stmt_intertPlayTime, 0, Player_GetAccountID(playerid));
    MySQL_ExecuteThreaded(stmt_intertPlayTime);
    return 1;
}

hook OnPlayerLogin(playerid)
{
    inline _load() {
        new
            hours,
            seconds;
        MySQL_BindResultInt(stmt_loadPlayTime, 0, seconds);
        MySQL_BindResultInt(stmt_loadPlayTime, 1, hours);

        if(MySQL_Statement_FetchRow(stmt_loadPlayTime)) {
            timeLeftCounter[playerid] = seconds;
            playerHoursPlayed[playerid] = hours;
        }
    }
    MySQL_BindInt(stmt_loadPlayTime, 0, Player_GetAccountID(playerid));
    MySQL_ExecuteParallel_Inline(stmt_loadPlayTime, using inline _load);
    return 1;
}

hook OnPlayerSpawn(playerid)
{
    new string[128];
    PlayerTextDrawShow(playerid, PlayerTD[playerid][0]);
    PlayerTextDrawShow(playerid, PlayerTD[playerid][1]);
    PlayerTextDrawShow(playerid, PlayerTD[playerid][2]);
    PlayerTextDrawShow(playerid, PlayerTD[playerid][3]);
    PlayerTextDrawShow(playerid, PlayerNameTD[playerid]);
    PlayerTextDrawShow(playerid, RelootTD[playerid]);
    PlayerTextDrawShow(playerid, weaponHolder[playerid]);
    PlayerTextDrawShow(playerid, formainui[playerid]);
    PlayerTextDrawShow(playerid, uppermainui[playerid]);
    PlayerTextDrawShow(playerid, header[playerid]);
    PlayerTextDrawShow(playerid, seperator[playerid]);
    PlayerTextDrawShow(playerid, timeAlive[playerid]);
    PlayerTextDrawShow(playerid, aliveTimeTimer[playerid]);
    PlayerTextDrawShow(playerid, zombiesKilled[playerid]);
    PlayerTextDrawShow(playerid, zombiesKilledCounter[playerid]);

    UI_StartTimer(playerid, timeLeftCounter[playerid], playerHoursPlayed[playerid]);

    formatex(string, sizeof(string), "%p", playerid);
    PlayerTextDrawSetString(playerid, PlayerNameTD[playerid], string);
    return 1;
}

stock UI_StartTimer(playerid, seconds, hours)
{
    if(!IsPlayerConnected(playerid)) {
        return 0;
    }

    new 
        string[30],
        mins,
        secs;
    
    mins = seconds / 60;
    secs = seconds % 60;

    format(string, sizeof(string), "%02d:%02d:%02d", hours, mins, secs);
    PlayerTextDrawSetString(playerid, aliveTimeTimer[playerid], string);

    MySQL_BindInt(stmt_updatePlayTime, 0, seconds);
    MySQL_BindInt(stmt_updatePlayTime, 1, hours);
    MySQL_BindInt(stmt_updatePlayTime, 2, Player_GetAccountID(playerid));
    MySQL_ExecuteThreaded(stmt_updatePlayTime);

    timeLeftTimer[playerid] = defer incrementTimer(playerid);
    timeLeftCounter[playerid] = seconds;

    return 1;
}

timer incrementTimer[1000](playerid)
{
    if(timeLeftCounter[playerid] ++ >= 3600) {
        playerHoursPlayed[playerid]++;
        timeLeftCounter[playerid] = 0;
    }
    UI_StartTimer(playerid, timeLeftCounter[playerid], playerHoursPlayed[playerid]);
}