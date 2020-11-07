#include <YSI_Coding\y_hooks>

/* STATEMENTS */
static
    Statement: stmt_playerSaveBlood,
    Statement: stmt_playerLoadBlood
;

/* VARIABLES */
static
    Float:blood[MAX_PLAYERS]
;

hook OnMySQLConnected()
{
    static const saveQuery[] = "\
    INSERT INTO players_blood (u_id, blood) \
    VALUES (?,?) \
    ON DUPLICATE KEY UPDATE blood = ? \
    ";
    stmt_playerSaveBlood = MySQL_PrepareStatement(MySQL_GetHandle(), saveQuery);

    static const loadQuery[] = "\
    SELECT \
        blood \
    FROM \
        players_blood \
    WHERE \
        u_id = ? \
    ";
    stmt_playerLoadBlood = MySQL_PrepareStatement(MySQL_GetHandle(), loadQuery);
    return 1;
}


