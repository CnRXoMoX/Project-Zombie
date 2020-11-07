#include <YSI_Coding\y_hooks>

static
    Float:gPlayerLastPos[MAX_PLAYERS][4],
    bool:gPlayerHasSavedPos[MAX_PLAYERS],
    bool:gPlayerJustJoined[MAX_PLAYERS],
    bool:gPlayerJustDied[MAX_PLAYERS], 
    Statement: stmt_playerSavePos,
    Statement: stmt_playerLoadPos,
    Statement: stmt_playerDeletePos
;

hook OnMySQLConnected()
{
    static const query[] = "\
        INSERT INTO \
            players_lastpos (u_id, posX, posY, posZ, posA, interior, worldid) \
        VALUES \
            (?,?,?,?,?,?,?) \
        ";
    stmt_playerSavePos = MySQL_PrepareStatement(MySQL_GetHandle(), query);

    static const loadQuery[] = "\
        SELECT \
            posX, \
            posY, \
            posZ, \
            posA \
        FROM \
            players_lastpos \
        WHERE \
            u_id = ? \
        ";
    stmt_playerLoadPos = MySQL_PrepareStatement(MySQL_GetHandle(), loadQuery);

    static const deleteQuery[] = "\
        DELETE FROM \
            players_lastpos \
        WHERE \
            u_id = ? \
        ";
    stmt_playerDeletePos = MySQL_PrepareStatement(MySQL_GetHandle(), deleteQuery);
    return 1;
}

hook MySQLPreClose()
{
    foreach(new i : Player)
    {
        new Float:pos[4];
        GetPlayerPos(i, pos[0], pos[1], pos[2]);
        GetPlayerFacingAngle(i, pos[3]);
        if(Player_IsLoggedIn(i)) {
            MySQL_BindInt(stmt_playerSavePos, 0, Player_GetAccountID(i));
            MySQL_BindFloat(stmt_playerSavePos, 1, pos[0]);
            MySQL_BindFloat(stmt_playerSavePos, 2, pos[1]);
            MySQL_BindFloat(stmt_playerSavePos, 3, pos[2]);
            MySQL_BindFloat(stmt_playerSavePos, 4, pos[3]);
            MySQL_BindInt(stmt_playerSavePos, 5, GetPlayerInterior(i));
            MySQL_BindInt(stmt_playerSavePos, 6, GetPlayerVirtualWorld(i));
            MySQL_ExecuteThreaded(stmt_playerSavePos);
        }
    }
    return 1;
}

hook OnPlayerConnect(playerid)
{
    gPlayerHasSavedPos[playerid] = false;
    gPlayerJustJoined[playerid] = false;
    gPlayerJustDied[playerid] = false; 
    return 1;
}

hook OnPlayerHasAccount(playerid)
{
    inline OnDataLoad()
    {
        new
            Float:tempPos[4];
        MySQL_BindResultFloat(stmt_playerLoadPos, 0, tempPos[0]);
        MySQL_BindResultFloat(stmt_playerLoadPos, 1, tempPos[1]);
        MySQL_BindResultFloat(stmt_playerLoadPos, 2, tempPos[2]);
        MySQL_BindResultFloat(stmt_playerLoadPos, 3, tempPos[3]);

        if(MySQL_Statement_FetchRow(stmt_playerLoadPos)) {
            gPlayerLastPos[playerid][0] = tempPos[0];
            gPlayerLastPos[playerid][1] = tempPos[1];
            gPlayerLastPos[playerid][2] = tempPos[2];
            gPlayerLastPos[playerid][3] = tempPos[3];
            gPlayerHasSavedPos[playerid] = true;
        }
    }
    MySQL_BindInt(stmt_playerLoadPos, 0, Player_GetAccountID(playerid));
    MySQL_ExecuteParallel_Inline(stmt_playerLoadPos, using inline OnDataLoad);
    return 1;
}

hook OnPlayerSpawn(playerid)
{
    if(gPlayerHasSavedPos[playerid]) {
        defer playerSpawnLastPos(playerid);
    }
    if(IsPlayerJustDied(playerid)) {
        defer justDiedTimer(playerid);
    }
    return 1;
}

hook OnPlayerDeath(playerid, killerid, reason)
{
    gPlayerJustDied[playerid] = true;
    return 1;
}

hook OnPlayerDisconnect(playerid, reason)
{
    new Float:pos[4];
    GetPlayerPos(playerid, pos[0], pos[1], pos[2]);
    GetPlayerFacingAngle(playerid, pos[3]);
    if(Player_IsLoggedIn(playerid)) {
        MySQL_BindInt(stmt_playerSavePos, 0, Player_GetAccountID(playerid));
        MySQL_BindFloat(stmt_playerSavePos, 1, pos[0]);
        MySQL_BindFloat(stmt_playerSavePos, 2, pos[1]);
        MySQL_BindFloat(stmt_playerSavePos, 3, pos[2]);
        MySQL_BindFloat(stmt_playerSavePos, 4, pos[3]);
        MySQL_BindInt(stmt_playerSavePos, 5, GetPlayerInterior(playerid));
        MySQL_BindInt(stmt_playerSavePos, 6, GetPlayerVirtualWorld(playerid));
        MySQL_ExecuteThreaded(stmt_playerSavePos);
    }
    return 1;
}

Player_DeleteSavedPos(playerid) {
    MySQL_BindInt(stmt_playerDeletePos, 0, Player_GetAccountID(playerid));
    MySQL_ExecuteThreaded(stmt_playerDeletePos);
}

timer justDiedTimer[500](playerid) {
    gPlayerJustDied[playerid] = false;
}

timer playerSpawnLastPos[500](playerid) {
    SetPlayerPos(playerid, gPlayerLastPos[playerid][0], gPlayerLastPos[playerid][1], gPlayerLastPos[playerid][2]);
    SetPlayerFacingAngle(playerid, gPlayerLastPos[playerid][3]);
    Player_DeleteSavedPos(playerid);
    gPlayerHasSavedPos[playerid] = false;
}

IsPlayerJustDied(playerid) {
    return gPlayerJustDied[playerid];
}