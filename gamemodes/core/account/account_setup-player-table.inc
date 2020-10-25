#include <YSI_Coding\y_hooks>

hook OnMySQLConnected()
{
    static const query[] = "\
        CREATE TABLE IF NOT EXISTS players \
        ( \
            u_id int(11) NOT NULL AUTO_INCREMENT, \
            username varchar(24) NOT NULL, \
            password char(250) NOT NULL, \
            register_date DATETIME NOT NULL DEFAULT CURRENT_TIMESTAMP(), \
            last_login DATETIME NOT NULL, \
            PRIMARY KEY (u_id), \
            UNIQUE KEY (username) \
        )";
    mysql_tquery(MySQL_GetHandle(), query);
    Logger_Log("Setting up 'players' table...");
    return 1;
}