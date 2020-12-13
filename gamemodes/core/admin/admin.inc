#include <admin_account>

#if SETUP_TABLE
    #include <admin_setup-table>
    #include <admin_setup-bans-table>
#endif

#include <admin_acmds>
#include <admin_ban>
#include <admin_ban-cmd>

#include <YSI_Coding\y_hooks>

hook OnGameModeInit()
{
    // Level 1 commands
    Admin_AddCommandToList(1, "/acmds");
    // Level 2 commands
    Admin_AddCommandToList(2, "/tempban");
    Admin_AddCommandToList(2, "/offtempban");
    Admin_AddCommandToList(2, "/unban");
    // Level 4 commands
    Admin_AddCommandToList(2, "/giveitem");
    return 1;
}