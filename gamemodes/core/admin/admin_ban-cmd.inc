ACMD:[2]tempban(playerid, params[])
{
    if (isnull(params) || isnumeric(params)) return SendSyntaxMsg(playerid, "/tempban <options: d(ay), m(onth), y(ear)>");
    new
        targetid = INVALID_PLAYER_ID,
        reason[MAX_BAN_REASON] = '\0',
        duration = -1,
        bool:success = false,
        interval = -1;

    if(!strcmp(params, "d", true, 1)) {
        if(sscanf(params, "{s[2]}riS(No Reason)["#MAX_BAN_REASON"]", targetid, duration, reason)) {
            return SendSyntaxMsg(playerid, "/tempban d (name/id) (duration) (reason)");
        }
        if(!IsPlayerConnected(targetid)) return SendErrorMsg(playerid, "Player is not connected!");
        if(targetid == playerid) return SendErrorMsg(playerid, "You can't ban yourself!");
        if(strlen(reason) > MAX_BAN_REASON) return SendErrorMsg(playerid, "Reason MAX length is 32");
        interval = 0;
    }
    if(!strcmp(params, "m", true, 1)) {
        if(sscanf(params, "{s[2]}riS(No Reason)["#MAX_BAN_REASON"]", targetid, duration, reason)) return SendSyntaxMsg(playerid, "/tempban m (name/id) (duration) (reason)");
        if(!IsPlayerConnected(targetid)) return SendErrorMsg(playerid, "Player is not connected!");
        if(targetid == playerid) return SendErrorMsg(playerid, "You can't ban yourself!");
        if(strlen(reason) > MAX_BAN_REASON) return SendErrorMsg(playerid, "Reason MAX length is 32");
        interval = 1;
    }
    if(!strcmp(params, "y", true, 1)) {
        if(sscanf(params, "{s[2]}riS(No Reason)["#MAX_BAN_REASON"]", targetid, duration, reason)) return SendSyntaxMsg(playerid, "/tempban y (name/id) (duration) (reason)");
        if(!IsPlayerConnected(targetid)) return SendErrorMsg(playerid, "Player is not connected!");
        if(targetid == playerid) return SendErrorMsg(playerid, "You can't ban yourself!");
        if(strlen(reason) > MAX_BAN_REASON) return SendErrorMsg(playerid, "Reason MAX length is 32");
        interval = 2;
    }

    if(interval != -1) {
        success = !!Ban_AddUser(targetid, playerid, reason, interval, duration);
    }

    if(success) {
        SendMsgF(playerid, COLOR_MODERATION, "**[ACCOUNT DISABLE]: You have Disabled %p's account for %s", targetid, reason);
        SendMsgAllF(COLOR_MODERATION, "**[ACCOUNT DISABLED]: %p (%d) has been banned for %s", targetid, targetid, reason);
        SendMsgF(targetid, COLOR_MODERATION, "**[ACCOUNT DISABLED]: You have been banned by an Admin For %s", reason);
        defer KickTimer(targetid);
        SendAdminCmdUsage(playerid, "/tempban", params);
    }
    return 1;
}

ACMD:[2]offtempban(playerid, params[])
{
    if (isnull(params) || isnumeric(params)) return SendSyntaxMsg(playerid, "/tempban <options: d(ay), m(onth), y(ear)>");
    new
        targetname[MAX_PLAYER_NAME],
        reason[MAX_BAN_REASON] = '\0',
        duration = -1,
        bool:success = false,
        interval = -1;

    if(!strcmp(params, "d", true, 1)) {
        if(sscanf(params, "{s[2]}s[24]iS(No Reason)["#MAX_BAN_REASON"]", targetname, duration, reason)) return SendSyntaxMsg(playerid, "/tempban d (name) (duration) (reason)");
        if(strlen(reason) > MAX_BAN_REASON) return SendErrorMsg(playerid, "Reason MAX length is 32");
        interval = 0;
    }
    if(!strcmp(params, "m", true, 1)) {
        if(sscanf(params, "{s[2]}s[24]iS(No Reason)["#MAX_BAN_REASON"]", targetname, duration, reason)) return SendSyntaxMsg(playerid, "/tempban m (name) (duration) (reason)");
        if(strlen(reason) > MAX_BAN_REASON) return SendErrorMsg(playerid, "Reason MAX length is 32");
        interval = 1;
    }
    if(!strcmp(params, "y", true, 1)) {
        if(sscanf(params, "{s[2]}s[24]iS(No Reason)["#MAX_BAN_REASON"]", targetname, duration, reason)) return SendSyntaxMsg(playerid, "/tempban y (name) (duration) (reason)");
        if(strlen(reason) > MAX_BAN_REASON) return SendErrorMsg(playerid, "Reason MAX length is 32");
        interval = 2;
    }

    foreach(new i : Player)
    {
        new staticName[MAX_PLAYER_NAME];
        GetPlayerName(i, staticName, sizeof staticName);
        if(!strcmp(targetname, staticName, true))
        {
            return SendErrorMsg(playerid, "Player is online use /tempban instead!");
        }
    }

    if(interval != -1) {
        success = !!OffBan_AddUser(targetname, playerid, reason, interval, duration);
    }

    if(success) {
        SendAdminCmdUsage(playerid, "/offtempban", params);
    }
    return 1;
}

ACMD:[3]unban(playerid, params[])
{
    if(isnull(params) || strval(params)) {
        return SendSyntaxMsg(playerid, "/unban <playername>");
    }
    if(strlen(params) > MAX_PLAYER_NAME) return SendErrorMsg(playerid, "MAX_PLAYER_NAME = 24, type the name again!");
    Ban_RemoveUser(params, playerid);
    SendAdminCmdUsage(playerid, "/unban", params);
    return 1;
}