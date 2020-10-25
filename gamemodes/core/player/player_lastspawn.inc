#include <YSI_Coding\y_hooks>

static
    Float:gPlayerPos[MAX_PLAYERS][4],
    bool:gPlayerJustJoined[MAX_PLAYERS],
    Statement: stmt_playerSavePos,
    Statement: stmt_playerLoadPos,
    Statement: stmt_playerDeletePos
;

hook OnMySQLConnected()
{
    static const query[] = "\
        INSERT INTO \
            player_lastpos (u_id, posX, posY, posZ, posA, interior, worldid) \
        VALUES \
            (?,?,?,?,?,?) \
        ";
    stmt_playerSavePos = MySQL_PrepareStatement(MySQL_GetHandle(), query);

    static const loadQuery[] = "\
        SELECT \
            posX, \
            posY, \
            posZ, \
            posA \
        FROM \
            player_lastpos \
        WHERE \
            u_id = ? \
        ";
    stmt_playerLoadPos = MySQL_PrepareStatement(MySQL_GetHandle(), loadQuery);

    static const deleteQuery[] = "\
        DELETE FROM \
            player_lastpos \
        WHERE \
            u_id = ? \
        ";
    stmt_playerDeletePos = MySQL_PrepareStatement(MySQL_GetHandle(), deleteQuery);
    return 1;
}

hook OnPlayerLogin(playerid)
{
    inline const OnPosLoad()
    {   
        new 
            Float:pos[4];
        MySQL_BindResultFloat(stmt_playerLoadPos, 0, pos[0]);
        MySQL_BindResultFloat(stmt_playerLoadPos, 1, pos[1]);
        MySQL_BindResultFloat(stmt_playerLoadPos, 2, pos[2]);
        MySQL_BindResultFloat(stmt_playerLoadPos, 3, pos[3]);
        
        if(MySQL_Statement_FetchRow(stmt_playerLoadPos)) {
            gPlayerPos[playerid][0] = pos[0];
            gPlayerPos[playerid][1] = pos[1];
            gPlayerPos[playerid][2] = pos[2];
            gPlayerPos[playerid][3] = pos[3];
            gPlayerJustJoined[playerid] = true;
            Player_DeleteSavedPos(playerid);
        }
    }
    MySQL_BindInt(stmt_playerLoadPos, 0, Player_GetAccountID(playerid));
    MySQL_ExecuteThreaded_Inline(stmt_playerLoadPos, using inline OnPosLoad);
    return 1;
}

hook OnPlayerSpawn(playerid)
{
    if(!Player_New(playerid) && gPlayerJustJoined[playerid])
    {
        SetPlayerPos(playerid, gPlayerPos[playerid][0], gPlayerPos[playerid][1], gPlayerPos[playerid][2]);
        SetPlayerFacingAngle(playerid, gPlayerPos[playerid][3]);
    }
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
        MySQL_BindFloat(stmt_playerSavePos, 4, GetPlayerInterior(playerid));
        MySQL_BindFloat(stmt_playerSavePos, 5, GetPlayerVirtualWorld(playerid));
        MySQL_ExecuteThreaded(stmt_playerSavePos);
    }
    return 1;
}

Player_DeleteSavedPos(playerid) {
    MySQL_BindInt(stmt_playerDeletePos, 0, Player_GetAccountID(playerid));
    MySQL_ExecuteThreaded(stmt_playerDeletePos);
}