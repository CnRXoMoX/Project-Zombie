#include <YSI_Coding\y_hooks>

#define IDLE_THIRST_RATE    (0.05)

hook OnPlayerSecondUpdate(playerid)
{
    if(!Player_IsSpawned(playerid)) return;

    new
        animidx = GetPlayerAnimationIndex(playerid),
        k,
        ud, 
        lr,
        Float:thirst;
    GetPlayerKeys(playerid, k, ud, lr);
    thirst = GetPlayerThirst(playerid);

    if(animidx == 43) // Sitting?
    {
        thirst -= IDLE_THIRST_RATE * 0.2;
    }
    else if(animidx == 1159) // Crounching
    {
        thirst -= IDLE_THIRST_RATE * 1.1;
    }
    else if(animidx == 1159) // Jumping
    {
        thirst -= IDLE_THIRST_RATE * 3.2;
    }
    else if(animidx == 1231) // Running
    {
        if(k & KEY_WALK)
        {
            thirst -= IDLE_THIRST_RATE * 1.2;
        }
        else if(k & KEY_SPRINT) // Sprinting
		{
			thirst -= IDLE_THIRST_RATE * 2.2;
		}
		else if(k & KEY_JUMP) // Jump
		{
			thirst -= IDLE_THIRST_RATE * 3.2;
		}
		else
		{
			thirst -= IDLE_THIRST_RATE * 2.0;
		}
    }
    else
    {
        thirst -= IDLE_THIRST_RATE;
    }

    if(thirst > 100)
        thirst = 100.0;
    /*if(thirst < 20.0)
        SetPlayerHP(playerid, GetPlayerHP(playerid) - (20.0 - food) / 30.0);*/
    if(thirst < 0.0)
        thirst = 0.0;
    
    SetPlayerThirst(playerid, thirst);
}