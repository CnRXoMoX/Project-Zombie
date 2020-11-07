#include <YSI_Coding\y_hooks>

/* Variables */
static 
    Float:gPlayerThirst[MAX_PLAYERS]
;

/* Statements */
static
    Statement: stmt_playerThirstSave,
    Statement: stmt_playerThirstLoad
;

hook OnMySQLConnected() {
    static const saveQuery[] = "\
    INSERT INTO players_thirst(u_id, thirst) \
    VALUES (?,?) \
    ON DUPLICATE KEY UPDATE thirst = ? \
    ";
    stmt_playerThirstSave = MySQL_PrepareStatement(MySQL_GetHandle(), saveQuery);

    static const loadQuery[] = "\
    SELECT \
        thirst \
    FROM \
        players_thirst \
    WHERE \
        u_id = ? \
    ";
    stmt_playerThirstLoad = MySQL_PrepareStatement(MySQL_GetHandle(), loadQuery);
    return 1;
}

hook OnPlayerLogin(playerid)
{
    inline _load() {
        new
            Float:thirst;
        MySQL_BindResultFloat(stmt_playerThirstLoad, 0, thirst);

        if(MySQL_Statement_FetchRow(stmt_playerThirstLoad)) {
            SetPlayerThirst(playerid, thirst, false);
        }
    }
    MySQL_BindInt(stmt_playerThirstSave, 0, Player_GetAccountID(playerid));
    MySQL_ExecuteParallel_Inline(stmt_playerThirstSave, using inline _load);
}

stock SetPlayerThirst(playerid, Float:value, bool:save = true) {
    gPlayerThirst[playerid] = value;
    if(save) {
        MySQL_BindInt(stmt_playerThirstSave, 0, Player_GetAccountID(playerid));
        MySQL_BindFloat(stmt_playerThirstSave, 1, value);
        MySQL_BindFloat(stmt_playerThirstSave, 2, value);
        MySQL_ExecuteThreaded(stmt_playerThirstSave);
    }
    return 1;
}

stock Float:GetPlayerThirst(playerid) return gPlayerThirst[playerid];