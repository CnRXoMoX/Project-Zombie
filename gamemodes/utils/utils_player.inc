static
    lastDrunkLevel[MAX_PLAYERS],
    currFPS[MAX_PLAYERS];

stock GetPlayerFPS(playerid) {
    new playerDrunkLevel = GetPlayerDrunkLevel(playerid);

    if(playerDrunkLevel < 100)
    {
        SetPlayerDrunkLevel(playerid, 2000);
    }
    else
    {
        if(lastDrunkLevel[playerid] != playerDrunkLevel)
        {
            currFPS[playerid] = (lastDrunkLevel[playerid] - playerDrunkLevel);

            lastDrunkLevel[playerid] = playerDrunkLevel;
            if((currFPS[playerid] > 0) && (currFPS[playerid] < 256))
            {
                return currFPS[playerid] - 1;
            }
        }
    }
    return 0;
}

stock Float:GetXYInFrontOfPlayer(playerid, &Float:q, &Float:w, Float:distance)
{
    new Float:a;
    GetPlayerPos(playerid, q, w, a);
    if (GetPlayerState(playerid) == PLAYER_STATE_DRIVER) GetVehicleZAngle(GetPlayerVehicleID(playerid), a);
    else GetPlayerFacingAngle(playerid, a);
    q += (distance * floatsin(-a, degrees));
    w += (distance * floatcos(-a, degrees));
    return a;
}

stock bool:RandomChance(percentage) {
	return (percentage >= random(100) + 1);
}

stock Float:Player_GetArmour(playerid) {
    new
        Float:playerArmour;

    GetPlayerArmour(playerid, playerArmour);
    return playerArmour;
}

stock Player_FacePlayer(playerid, giveplayerid) {
    // function made by Nero_3D.
    new
        Float: pX,
        Float: pY,
        Float: pZ,
        Float: gX,
        Float: gY,
        Float: gZ
    ;
    if(GetPlayerPos(playerid, pX, pY, pZ) && GetPlayerPos(giveplayerid, gX, gY, gZ)) {
        SetPlayerFacingAngle(playerid, (pX = -atan2((gX - pX), (gY - pY))));
        return SetPlayerFacingAngle(giveplayerid, (pX + 180.0));
    }
    return false;
}

/*stock Player_GetClosestWanted(playerid) {
    new
        closestID = INVALID_PLAYER_ID;

    foreach(new i : Player) {

        if(playerid == i) {
            continue;
        }

        if(Player_GetClosestPlayer(playerid, 5.0) && Player_GetWantedLevel(i) >= 3) {
            closestID = i;
            break;
        }
    }
    return closestID;
}*/

stock Player_IsNearPlayer(playerid, targetid, Float:radius)
{
	new
        Float:x,
        Float:y,
        Float:z;

	GetPlayerPos(playerid, x, y, z);

    new
        matchingVW = GetPlayerVirtualWorld(playerid) == GetPlayerVirtualWorld(targetid),
        matchingInt = GetPlayerInterior(playerid) == GetPlayerInterior(targetid),
        inRange = IsPlayerInRangeOfPoint(targetid, radius, x, y, z);

	return matchingVW && matchingInt && inRange;
}

stock Player_GetClosestPlayer(playerid, Float:range = 10000.0)
{
    new
        Float:x,
        Float:y,
        Float:z;

    GetPlayerPos(playerid, x, y, z);

    return GetClosestPlayerFromPoint(x, y, z, range, playerid);
}

static stock GetClosestPlayerFromPoint(Float:x, Float:y, Float:z, &Float:lowestdistance = 10000.0, exceptionid = INVALID_PLAYER_ID)
{
    new
        Float:px,
        Float:py,
        Float:pz,
        Float:distance,
        closestplayer = -1;

    foreach(new i : Player)
    {
        if (i == exceptionid)
            continue;

        GetPlayerPos(i, px, py, pz);

        distance = Distance(px, py, pz, x, y, z);

        if (distance < lowestdistance)
        {
            lowestdistance = distance;
            closestplayer = i;
        }
    }
    return closestplayer;
}