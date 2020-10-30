/* FIRST AID KITS */
forward OnPlayerRequestToUseBandage(playerid);
forward OnPlayerRequestToUseMedkit(playerid);
forward OnPlayerRequestToUsePainkiller(playerid);
forward OnPlayerRequestToUseAntibiotics(playerid);
forward OnPlayerRequestToUseMorphine(playerid);

/* BAGS */
forward OnPlayerRequestToUseBagTraveler(playerid);

/* OTHERS */
forward OnPlayerRequestToUseGPS(playerid);

public OnPlayerRequestToUseGPS(playerid)
{
    SendServerMsg(playerid, "This is for you to see the map");
    return 1;
}