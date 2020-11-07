#include <YSI_Coding\y_hooks>

/* Variables */
static
    Float:gPlayerFood[MAX_PLAYERS]
;

/* Statements */
static
    Statement: stmt_playerFoodSave,
    Statement: stmt_playerFoodLoad
;

hook OnMySQLConnected()
{
    static const saveQuery[] = "\
    INSERT INTO players_food(u_id, food) \
    VALUES (?,?) \
    ON DUPLICATE KEY UPDATE food = ? \
    ";
    stmt_playerFoodSave = MySQL_PrepareStatement(MySQL_GetHandle(), saveQuery);

    static const loadQuery[] = " \
    SELECT \
        food \
    FROM \
        players_food \
    WHERE \
        u_id = ? \
    ";
    stmt_playerFoodLoad = MySQL_PrepareStatement(MySQL_GetHandle(), loadQuery);
    return 1;
}

hook OnPlayerLogin(playerid)
{
    inline _load() {
        new 
            Float:food;
        MySQL_BindResultFloat(stmt_playerFoodLoad, 0, food);

        if(MySQL_Statement_FetchRow(stmt_playerFoodLoad)) {
            SetPlayerFood(playerid, food, false);
        }
    }
    MySQL_BindInt(stmt_playerFoodLoad, 0, Player_GetAccountID(playerid));
    MySQL_ExecuteParallel_Inline(stmt_playerFoodLoad, using inline _load);
    return 1;
}

stock SetPlayerFood(playerid, Float:value, bool:save = true)
{
    gPlayerFood[playerid] = value;
    if(save) {
        MySQL_BindInt(stmt_playerFoodSave, 0, Player_GetAccountID(playerid));
        MySQL_BindFloat(stmt_playerFoodSave, 1, value);
        MySQL_BindFloat(stmt_playerFoodSave, 2, value);
        MySQL_ExecuteThreaded(stmt_playerFoodSave);
    }
    return 1;
}

stock Float:GetPlayerFood(playerid) return gPlayerFood[playerid];   