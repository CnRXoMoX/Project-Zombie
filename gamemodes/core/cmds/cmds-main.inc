static 
    cmd_Cooldown[MAX_PLAYERS],
    cmd_Count[MAX_PLAYERS]
;

public OnPlayerCommandReceived(playerid, cmd[])
{
    if(!Player_IsLoggedIn(playerid)) return SendErrorMsg(playerid, "You need to login first before executing a command");

    if(gettime() < cmd_Cooldown[playerid]) {
        cmd_Count[playerid]++;

        if(cmd_Count[playerid] >= 3) {
            SendServerMsgF(playerid, "Do not spam commands. Count:"C_GREY"%d", cmd_Count[playerid]);
            return 0;
        }
    }
    else {
        if(cmd_Count[playerid] > 0) {
            cmd_Count[playerid] --;
        }
    }

    cmd_Cooldown[playerid] = gettime() + 3;
    return 1;
}

public OnPlayerCommandPerformed(playerid, cmd[], success)
{
    if(!success)
        return SendErrorMsg(playerid, "Command doesn't exist!");

    cmd_Cooldown[playerid] = gettime() + 3;
    return 1;
}