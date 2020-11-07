#define BCRYPT_COST 12

#define PLAYER_DEBUG_HANDLER    "player"
#define SERVER_DEBUG_HANDLER    "server"
#define ADMIN_DEBUG_HANDLER     "admin"

#define SQL_DATETIME_FORMAT     "%d %M %Y at %r"
#define SQL_DATE_FORMAT         "%d %M %Y"

#define MAX_BAN_REASON 32

#define PRESSED(%0) \
    (((newkeys & (%0)) == (%0)) && ((oldkeys & (%0)) != (%0)))


/* DIALOG IDS */
#define INVENTORY_DIALOG    (1)

enum Gender
{
    FEMALE = 0,
    MALE
};