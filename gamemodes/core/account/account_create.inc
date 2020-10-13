#include <YSI_Visual\y_dialog>
#include <YSI_Coding\y_hooks>

static 
    Statement:stmt_insertPlayerAccount,
    bool:PlayerFirstTime[MAX_PLAYERS]
;

static
    const RegisterDialogMessage[] = "Hello "C_GREY"%p "C_WHITE"Welcome to "C_YELLOW"%s";

hook OnMySQLConnected()
{
    stmt_insertPlayerAccount = MySQL_PrepareStatement(MySQL_GetHandle(), "INSERT INTO players (username, password) VALUES (?, ?)");
    return 1;
}

stock Account_PromptRegister(playerid) {
    inline const _response(pid, dialogid, response, listitem, string:inputtext[]) {
        #pragma unused pid, dialogid, listitem
        if (!response) {
            Kick(playerid);
            return 1;
        }
        Account_Create(playerid, inputtext);
    }

    new
        string[48 + MAX_PLAYER_NAME + 16];
    format(string, sizeof(string), RegisterDialogMessage, playerid, SERVER_NAME);

    Dialog_ShowCallback(playerid, using inline _response, DIALOG_STYLE_PASSWORD, "Please register...", string, "Register", "Leave");
    return 1;
}

static Account_Create(playerid, const password[]) {
    if(!(3 <= strlen(password) <= 20)) {
        SendErrorMsg(playerid, "Invalid length on the password. It should be between 3-20 characters" );
        Account_PromptRegister(playerid);
        return;
    }

    if(isnumeric(password)) {
        SendErrorMsg(playerid, "Your password is invalid. The password should include alphabets.");
        Account_PromptRegister(playerid);
        return;
    }

    inline const OnPasswordHash(string:hash[])
    {
        Account_InsertToDatabase(playerid, hash);
    }
    BCrypt_HashInline(password, BCRYPT_COST, using inline OnPasswordHash);
}

stock Account_InsertToDatabase(playerid, const hash[]) {
    inline const OnRegister() {
        Player_SetAccountID(playerid, cache_insert_id());

        static const
            msg_content[] = "Hello ~p~%p, ~w~You're now registered to DayZ and Automatically logged in";
        
        CallLocalFunction("OnPlayerRegister", "i", playerid);
        Player_SetNew(playerid, true);
        TogglePlayerSpectating(playerid, false);
        SendServerMsgF(playerid, msg_content, playerid);
    }

    new username[MAX_PLAYER_NAME];
    GetPlayerName(playerid, username, sizeof(username));

    MySQL_Bind(stmt_insertPlayerAccount, 0, username);
    MySQL_Bind(stmt_insertPlayerAccount, 1, hash);
    MySQL_ExecuteThreaded_Inline(stmt_insertPlayerAccount, using inline OnRegister);
}

stock Player_New(playerid) return PlayerFirstTime[playerid];
stock Player_SetNew(playerid, bool:status) {
    PlayerFirstTime[playerid] = status;
}