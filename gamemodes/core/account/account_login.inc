#include <YSI_Visual\y_dialog>
#include <YSI_Coding\y_hooks>
#include <formatex>
#include <logger>

static
    gPlayerHash[MAX_PLAYERS][250],
    bool:gPlayerLoginStatus[MAX_PLAYERS],
    PlayerAttempts[MAX_PLAYERS];

#define MAX_PASSWORD_ATTEMPT     (5)

hook OnPlayerConnect(playerid)
{
    gPlayerHash[playerid][0] = EOS;
    gPlayerLoginStatus[playerid] = false;
    return 1;
}

//global
void:Account_PromptLogin(playerid, const password[], len = sizeof(password)) {
    if(isnull(gPlayerHash[playerid])) {
        strcat(gPlayerHash[playerid], password, len);
    }

    inline PromptLoginResponse(pid, dialogid, response, listitem, string:inputtext[]) {
        #pragma unused pid, dialogid, listitem

        if(!response) {
            Kick(playerid);
            return;
        }

        inline const OnPasswordVerify(bool: success)
        {
            if(!success) {
                PlayerAttempts[playerid] ++;

                if(PlayerAttempts[playerid] >= MAX_PASSWORD_ATTEMPT) {
                    SendErrorMsg(playerid, "You have been kicked from the server for attempting to login numerous times.");
                    Kick(playerid);

                    dbg(PLAYER_DEBUG_HANDLER, "player has been kicked for too many login attempts",
                        _p("username", playerid),
                        _i("uid", Player_GetAccountID(playerid))
                    );
                    return;
                }

                Account_PromptLogin(playerid, gPlayerHash[playerid]);
                SendErrorMsgF(playerid, "Wrong password, try again! - Attempts: [%i/%i]", PlayerAttempts[playerid], MAX_PASSWORD_ATTEMPT);

                dbg(PLAYER_DEBUG_HANDLER, "player failed to login",
                    _i("attemps", PlayerAttempts[playerid]),
                    _p("username", playerid),
                    _i("uid", Player_GetAccountID(playerid))
                );
                return;
            }

            dbg(PLAYER_DEBUG_HANDLER, "player successfully logged in",
                _p("username", playerid),
                _i("uid", Player_GetAccountID(playerid))
            );

            PlayerAttempts[playerid] = 0;
            Account_NotifySuccess(playerid);
            CallLocalFunction("OnPlayerLogin", "i", playerid);
            
        }
        BCrypt_CheckInline(inputtext, gPlayerHash[playerid], using inline OnPasswordVerify);
    }

    new string[MAX_PLAYER_NAME + 35];
    format(string, sizeof(string), "Hello %p! Welcome back to %s", playerid, SERVER_NAME);

    Dialog_ShowCallback(playerid,
        using inline PromptLoginResponse,   // Handler
        DIALOG_STYLE_PASSWORD,              // Style
        "Please Login...",                  // Title
        string,                             // Content
        "Login",                            // Button Left
        "Leave");                           // Button Right
}

stock Account_NotifySuccess(playerid)
{
    SendServerMsgF(playerid, "You're now logged in!");
    return 1;
}

hook OnPlayerRequestClass(playerid, classid)
{
    SpawnPlayer(playerid);
    return 1;
}

stock Player_IsLoggedIn(playerid) {
    return gPlayerLoginStatus[playerid];
}

stock Player_SetLoginStatus(playerid, bool:status) {
    return gPlayerLoginStatus[playerid] = status;
}