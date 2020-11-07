#include <YSI_Coding\y_hooks>

hook OnMySQLConnected()
{
    static const query[] = "\
    CREATE TALBE IF NOT EXISTS players_thirst \
    ( \
        u_id INT(11) NOT NULL, \
        thirst FLOAT NOT NULL, \
        PRIMARY KEY (u_id), \
        FOREIGN KEY (u_id) REFERENCES players(u_id) \
        ON DALETE CASCADE \
        ON UPDATE RESTRICT \
    )";
    mysql_tquery(MySQL_GetHandle(), query);

    Logger_Log("Setting up 'players_thirst' table...");
}