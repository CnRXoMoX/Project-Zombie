#include <YSI_Coding\y_hooks>

#define IDLE_FOOD_RATE  (0.004)

hook OnPlayerSecondUpdate(playerid) 
{
    if(!Player_IsSpawned(playerid)) return;

    new
        animidx = GetPlayerAnimationIndex(playerid),
        k,
        ud,
        lr,
        Float:food;
    GetPlayerKeys(playerid, k, ud, lr);
    food = GetPlayerFood(playerid);

    if(animidx == 43) // Sitting?
    {
        food -= IDLE_FOOD_RATE * 0.2;
    }
    else if(animidx == 1159) // Crounching
    {
        food -= IDLE_FOOD_RATE * 1.1;
    }
    else if(animidx == 1159) // Jumping
    {
        food -= IDLE_FOOD_RATE * 3.2;
    }
    else if(animidx == 1231) // Running
    {
        if(k & KEY_WALK)
        {
            food -= IDLE_FOOD_RATE * 1.2;
        }
        else if(k & KEY_SPRINT) // Sprinting
		{
			food -= IDLE_FOOD_RATE * 2.2;
		}
		else if(k & KEY_JUMP) // Jump
		{
			food -= IDLE_FOOD_RATE * 3.2;
		}
		else
		{
			food -= IDLE_FOOD_RATE * 2.0;
		}
    }
    else
    {
        food -= IDLE_FOOD_RATE;
    }

    if(food > 100.0)
        food = 100.0;
    
    /*if(food < 20.0)
        SetPlayerHP(playerid, GetPlayerHP(playerid) - (20.0 - food) / 30.0);*/
    if(food < 0.0)
        food = 0.0;

    SetPlayerFood(playerid, food);
    return;
}