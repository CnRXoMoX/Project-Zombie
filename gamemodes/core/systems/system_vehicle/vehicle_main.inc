#include <vehicle_functions>
#include <vehicle_inv>
#include <vehicle_showinv>

#include <YSI_Coding\y_hooks>

hook OnGameModeInit()
{
    Vehicle_Create(420, 2586.707275, 2772.758544, 9.795619, 0, 0, 0);
    return 1;
}