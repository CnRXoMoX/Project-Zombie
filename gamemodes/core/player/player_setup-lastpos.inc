#include <YSI_Coding\y_hooks>

hook OnMySQLConnected()
{
    static const query[] = "\
        CREATE TABLE IF NOT EXISTS players_lastpos \
        ( \
            u_id int(11) NOT NULL AUTO_INCREMENT, \
            posX FLOAT NOT NULL, \
            posY FLOAT NOT NULL, \
            posZ FLOAT NOT NULL, \
            posA FLOAT NOT NULL, \
            interior int(11) NOT NULL DEFAULT '0', \
            worldid int(11) NOT NULL DEFAULT '0', \
            PRIMARY KEY (u_id), \
            FOREIGN KEY (u_id) REFERENCES players(u_id), \
            ON DELETE CASCADE \
            ON UPDATE RESTRICT \
        )";
    mysql_tquery(MySQL_GetHandle(), query);
    log("Setting up 'players_lastpos' table...");
    return 1;
}