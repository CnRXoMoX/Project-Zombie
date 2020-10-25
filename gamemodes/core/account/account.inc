#include <account_create>
#include <account_login>
#include <account_stats>
#if SETUP_TABLE
    #include <account_setup-player-table>
    #include <account_setup-stats>
#endif

#include <YSI_Coding\y_hooks>

static
    Player_UID[MAX_PLAYERS],
    Statement: stmt_checkPlayer
;

hook OnMySQLConnected()
{
    stmt_checkPlayer = MySQL_PrepareStatement(MySQL_GetHandle(), "SELECT u_id, password FROM players WHERE username=?");
    return 1;
}

hook OnPlayerConnect(playerid) {
    Player_UID[playerid] = 0;
    TogglePlayerSpectating(playerid, true);
    return 1;
}

hook OnPlayerPassedBanCheck(playerid)
{
    inline const OnDataLoad() {
        new
            playerUID,
            playerHash[250];
        
        MySQL_BindResultInt(stmt_checkPlayer, 0, playerUID);
        MySQL_BindResult(stmt_checkPlayer, 1, playerHash, sizeof(playerHash));

        if(MySQL_Statement_FetchRow(stmt_checkPlayer)) {
            Player_SetAccountID(playerid, playerUID);
            Account_PromptLogin(playerid, playerHash);
        } else {
            Account_PromptRegister(playerid);
        }
    }
    
    new playerName[MAX_PLAYER_NAME];
    GetPlayerName(playerid, playerName, sizeof(playerName));

    MySQL_Bind(stmt_checkPlayer, 0, playerName);
    MySQL_ExecuteParallel_Inline(stmt_checkPlayer, using inline OnDataLoad);
}

stock Player_SetAccountID(playerid, value) {
    return Player_UID[playerid] = value;
}

stock Player_GetAccountID(playerid) {
    return Player_UID[playerid];
}