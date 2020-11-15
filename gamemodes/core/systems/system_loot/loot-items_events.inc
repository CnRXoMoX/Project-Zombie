/* FIRST AID KITS */
forward OnPlayerRequestToUseBandage(playerid);
forward OnPlayerRequestToUseMedkit(playerid);
forward OnPlayerRequestToUsePainkiller(playerid);
forward OnPlayerRequestToUseAntibiotics(playerid);
forward OnPlayerRequestToUseMorphine(playerid);

/* BAGS */
forward OnPlayerRequestToUseSmallBP(playerid); // 2
forward OnPlayerRequestToUseMediumBP(playerid); // 3
forward OnPlayerRequestToUseTravelBag(playerid); // 4
forward OnPlayerRequestToUseCZBP(playerid); // 5
forward OnPlayerRequestToUseAssaulBP(playerid); // 6

/* OTHERS */
forward OnPlayerRequestToUseGPS(playerid);

public OnPlayerRequestToUseGPS(playerid)
{
    SendServerMsg(playerid, "This is for you to see the map");
    return 1;
}

public OnPlayerRequestToUseSmallBP(playerid)
{
    GivePlayerBag(playerid, 2);
    return 1;
}

public OnPlayerRequestToUseMediumBP(playerid)
{
    GivePlayerBag(playerid, 3);
    return 1;
}

public OnPlayerRequestToUseTravelBag(playerid)
{
    GivePlayerBag(playerid, 4);
    return 1;
}

public OnPlayerRequestToUseCZBP(playerid)
{
    GivePlayerBag(playerid, 5);
    return 1;
}

public OnPlayerRequestToUseAssaulBP(playerid)
{
    GivePlayerBag(playerid, 6);
    return 1;
}