/* FIRST AID KITS */
forward PlayerRequestToUseBandage(playerid);
forward PlayerRequestToUseMedkit(playerid);
forward PlayerRequestToUsePainkiller(playerid);
forward PlayerRequestToUseAntibiotics(playerid);
forward PlayerRequestToUseMorphine(playerid);

/* BAGS */
forward PlayerRequestToUseBagTraveler(playerid);

public PlayerRequestToUseMedkit(playerid)
{
    SetPlayerArmour(playerid, 100);
    return 1;
}