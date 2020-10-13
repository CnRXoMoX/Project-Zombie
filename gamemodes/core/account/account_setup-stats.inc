#include <YSI_Coding\y_hooks>

hook OnMySQLConnected()
{
    static const query[] = "\
        CREATE TABLE IF NOT EXISTS players_stats \
        ( \
            u_id int(11) NOT NULL AUTO_INCREMENT, \
            kills mediumint(8) NOT NULL DEFAULT '0', \
            deaths mediumint(8) NOT NULL DEFAULT '0', \
            coins bigint(20) NOT NULL DEFAULT '0', \
            skin smallint(4) NOT NULL DEFAULT '0', \
            PRIMARY KEY (u_id), \
            FOREIGN KEY (u_id) REFERENCES players(u_id) \
            ON DELETE CASCADE \
            ON UPDATE RESTRICT \
        )";
    mysql_tquery(MySQL_GetHandle(), query);
    log("Setting up 'players_stats' table...");
    return 1;
}