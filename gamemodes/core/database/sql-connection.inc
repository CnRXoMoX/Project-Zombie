#include <YSI_Coding\y_hooks>

static
    MySQL:MySQL_Handler;

static const
    MYSQL_HOST[]    = "localhost",
    MYSQL_PW[]      = "",
    MYSQL_DB[]      = "dayz",
    MYSQL_USER[]    = "root";

hook OnGameModeInit()
{
    new MySQLOpt: option_id = mysql_init_options();
    
    mysql_set_option(option_id, AUTO_RECONNECT, true);

    MySQL_Handler = mysql_connect(MYSQL_HOST, MYSQL_USER, MYSQL_PW, MYSQL_DB, option_id);

    if(MySQL_Handler == MYSQL_INVALID_HANDLE || mysql_errno(MySQL_Handler) != 0)
    {
        fatal("MySQL Failed to connect shutting down!");
        SendRconCommand("exit");
        return 1;
    }

    log("MySQL Successfuly Loaded");
    CallLocalFunction("OnMySQLConnected", "");
    return 1;
}

hook OnGameModeExit()
{
    log("MySQL Shut down");
    CallLocalFunction("MySQLPreClose", "");
    mysql_close(MySQL_Handler);
    return 1;
}

stock MySQL:MySQL_GetHandle() {
    return MySQL_Handler;
}