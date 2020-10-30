#include <YSI_Coding\y_hooks>

hook OnMySQLConnected() 
{
    static const query[] = "\
    CREATE TABLE IF NOT EXISTS players_alivetime \
    ( \
        u_id int(11) NOT NULL, \
        seconds int(11) NOT NULL DEFAULT '0', \
        hours int(11) NOT NULL DEFAULT '0', \
        PRIMARY KEY (u_id), \
        FOREIGN KEY (u_id) REFERENCES players(u_id) \
        ON DELETE CASCADE \
        ON UPDATE RESTRICT \
    )";
    mysql_tquery(MySQL_GetHandle(), query);

    Logger_Log("SETTING UP 'players_alivetime' table...");
    return 1;
}