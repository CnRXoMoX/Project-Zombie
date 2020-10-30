#include <loot-items>
#include <pinventory_functions>
#include <pinventory-main> // Something in this include needs to go first
#include <loot-main>
//#include <vehicle_main>

//#include <zombies-main>

#include <YSI_Coding\y_hooks>

hook OnGameModeInit()
{
    new Float:test = frandom(0.0, 100.0);
    printf("%.1f", test);
    return 1;
}