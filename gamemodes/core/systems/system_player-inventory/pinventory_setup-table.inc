#include <YSI_Coding\y_hooks>

hook OnMySQLConnected()
{
    static const query[] = "\
    CREATE TABLE IF NOT EXISTS player_lootinv \
    ( \
        u_id INT(11) NOT NULL AUTO_INCREMENT, \
        slot INT(11) NOT NULL, \
        item_id INT(11) NOT NULL, \
        PRIMARY KEY (u_id), \
        FOREIGN KEY (u_id) REFERENCES players(u_id) \
        ON DELETE CASCADE \
        ON UPDATE RESTRICT \
    )";
    mysql_tquery(MySQL_GetHandle(), query);
    Logger_Log("Setting up 'player_lootinv' table...");
    return 1;
}