#include <FCNPC>
#include <mapandreas>
#include <YSI_Coding\y_hooks>

#define MAX_ZOMBIES (20)
static
    gSpawnedZombies, 
    bool:IsAZombie[MAX_PLAYERS], 
    Timer:gZombieTimer[MAX_PLAYERS], 
    Timer:gZombieSpawnTimer,
    gZombieIsAttack[MAX_PLAYERS];

new
    Float:zombieSpawns[][4] =
{
    {-2542.5759,2324.0122,4.9844,82.1170},
    {-2242.8242,2345.2800,5.3902,14.1956},
    {-1911.6620,2422.7727,52.6096,269.1553},
    {-1511.5007,2577.4980,55.8359,317.7225},
    {-1258.2908,2663.8604,48.5697,285.7621},
    {-821.8821,2749.8655,46.0000,285.7621},
    {-590.7568,2685.3401,73.8637,285.7621},
    {-286.6721,2701.0964,62.5391,270.0953},
    {-280.5756,2589.6130,63.3337,197.7147},
    {2786.2183,-2436.7859,13.6340,82.3043},
    {-1308.4493,504.9661,11.1953,132.5},
    {272.6040,1989.7307,17.6406,268.3605},
    {-26.9938,2373.4287,23.3340,47.1683},
    {1792.0466,2469.8860,7.1585,97.9287},
    {1803.1254,2019.6487,4.0078,52.5299},
    {2108.9143,1971.9635,10.6900,329.6292},
    {2235.9885,2441.8914,10.6719,59.6292},
    {2045.3735,2478.0754,10.8203,169.8510},
    {2763.3447,2264.9346,10.8203,193.3513},
    {2761.9985,1946.8805,12.1766,85.8769},
    {2776.7224,1289.0688,10.7500,207.4514},
    {2770.5554,1041.4323,10.7500,179.2511},
    {2556.0176,773.7820,10.4236,31.2115},
    {2031.5289,867.6794,6.9608,205.0897},
    {1803.5732,795.7164,11.2150,107.4971},
    {1683.2909,424.1697,19.1272,166.4043},
    {1635.5233,224.0716,30.7120,166.4043},
    {1568.2250,-1693.5483,5.8906,177.0983},
    {-1604.8442,732.9442,-5.2344,37.6041},
    {1609.5922,1820.9641,10.8280,348.1614},
    {1561.1786,-24.5144,20.5611,166.4043},
    {1251.6511,-359.6993,3.6166,21.8113},
    {659.4545,-484.1760,16.1875,49.0716},
    {287.5155,59.7256,2.0705,136.9508},
    {204.8613,-66.6794,2.0705,136.9508},
    {-150.9496,-189.0110,2.0705,136.9508},
    {-141.7663,-366.9684,2.3751,136.9508},
    {-61.0981,-1116.5044,1.0781,159.1977},
    {-72.2603,-1510.5847,2.3197,263.2253},
    {294.1158,-1730.1440,4.3490,83.2253},
    {758.9001,-1774.3301,13.0176,263.2253},
    {1051.0582,-1824.3665,13.4656,263.2253},
    {1117.5380,-1495.9845,14.8806,158.1127},
    {1255.0277,-1295.0862,13.2834,338.1127},
    {1737.1638,-1297.2551,15.0717,287.9790},
    {2043.2405,-1194.0485,23.4722,287.9790},
    {2295.2156,-1168.6434,26.2969,256.0187},
    {2719.5735,-1280.6475,57.3341,256.0187},
    {2737.5974,-1631.4252,12.8438,6.4580},
    {2503.5813,-1819.8751,12.8438,121.2840},
    {2444.7588,-1671.6128,12.8438,76.4770},
    {2080.0403,-1731.2953,12.8438,135.3842},
    {1957.6324,-2160.9009,13.3828,135.3842},
    {1418.9562,-2166.7876,13.3901,90.2638},
    {-2860.2517,123.7832,11.1912,331.1730},
    {-2840.0906,521.3478,4.8244,3.1333},
    {-2816.4668,905.3797,44.0547,183.1333},
    {-2602.4771,1378.9128,7.1784,120.4660,},
    {-2683.0396,2050.3188,56.6777,9.0867},
    {-1568.6206,2088.4973,50.4226,94.1458},
    {-1033.3961,1238.3406,32.2326,217.4319},
    {-306.0912,1531.4260,75.3594,131.5777},
    {-2723.4639,-314.8138,7.1839,43.5562},  // golf course spawn
    {-2694.5344,64.5550,4.3359,95.0190},  // in front of a house
    {-2458.2000,134.5419,35.1719,303.9446},  // hotel
    {-2796.6589,219.5733,7.1875,88.8288},  // house
    {-2706.5261,397.7129,4.3672,179.8611},  // park
    {-2866.7683,691.9363,23.4989,286.3060},  // house
    {-2764.9543,785.6434,52.7813,357.6817},  // donut shop
    {-2660.9402,883.2115,79.7738,357.4440},  // house
    {-2861.0796,1047.7109,33.6068,188.2750}, //  parking lot
    {-2629.2009,1383.1367,7.1833,179.7006},  // parking lot at the bridge
    {-2079.6802,1430.0189,7.1016,177.6486},  // pier
    {-1660.2294,1382.6698,9.8047,136.2952}, //  pier 69
    {-1674.1964,430.3246,7.1797,226.1357},  // gas station]
    {-1954.9982,141.8080,27.1747,277.7342},  // train station
    {-1956.1447,287.1091,35.4688,90.4465},  // car shop
    {-1888.1117,615.7245,35.1719,128.4498},  // random
    {-1922.5566,886.8939,35.3359,272.1293},  // random
    {-1983.3458,1117.0645,53.1243,271.2390},  // church
    {-2417.6458,970.1491,45.2969,269.3676},  // gas station
    {-2108.0171,902.8030,76.5792,5.7139},  // house
    {-2097.5664,658.0771,52.3672,270.4487},  // random
    {-2263.6650,393.7423,34.7708,136.4152},  // random
    {-2287.5027,149.1875,35.3125,266.3989},  // baseball parking lot
    {-2039.3571,-97.7205,35.1641,7.4744},  // driving school
    {-1867.5022,-141.9203,11.8984,22.4499},  // factory
    {-1537.8992,116.0441,17.3226,120.8537},  // docks ship
    {-1708.4763,7.0187,3.5489,319.3260},  // docks hangar
    {-1427.0858,-288.9430,14.1484,137.0812},  // airport
    {-2173.0654,-392.7444,35.3359,237.0159},  // stadium
    {-2320.5286,-180.3870,35.3135,179.6980},  // burger shot
    {-2930.0049,487.2518,4.9141,3.8258},
    {1435.8024,2662.3647,11.3926,1.1650}, //  Northern train station
    {1457.4762,2773.4868,10.8203,272.2754}, //  Northern golf club
    {1739.6390,2803.0569,14.2735,285.3929}, //  Northern housing estate 1
    {1870.3096,2785.2471,14.2734,42.3102}, //  Northern housing estate 2
    {1959.7142,2754.6863,10.8203,181.4731}, //  Northern house 1
    {2314.2556,2759.4504,10.8203,93.2711}, //  Northern industrial estate 1
    {2216.5674,2715.0334,10.8130,267.6540}, //  Northern industrial estate 2
    {2101.4192,2678.7874,10.8130,92.0607}, //  Northern near railway line
    {1951.1090,2660.3877,10.8203,180.8461}, //  Northern house 2
    {1666.6949,2604.9861,10.8203,179.8495}, //  Northern house 3
    {2808.3367,2421.5107,11.0625,136.2060}, //  Northern shopping centre
    {2633.3203,2349.7061,10.6719,178.7175}, //  V-Rock
    {2606.6348,2161.7490,10.8203,88.7508}, //  South V-Rock
    {2616.5286,2100.6226,10.8158,177.7834}, //  North Ammunation 1
    {2491.8816,2397.9370,10.8203,266.6003}, //  North carpark 1
    {2531.7891,2530.3223,21.8750,91.6686}, //  North carpark 2
    {2340.6677,2530.4324,10.8203,177.8630}, //  North Pizza Stack
    {2097.6855,2491.3313,14.8390,181.8117}, //  Emerald Isle
    {1893.1000,2423.2412,11.1782,269.4385}, //  Souvenir shop
    {1698.9330,2241.8320,10.8203,357.8584}, //  Northern casino
    {1479.4559,2249.0769,11.0234,306.3790}, //  Baseball stadium 1
    {1298.1548,2083.4016,10.8127,256.7034}, //  Baseball stadium 2
    {1117.8785,2304.1514,10.8203,81.5490}
};

hook OnGameModeInit()
{
    MapAndreas_Init(MAP_ANDREAS_MODE_FULL);
    gZombieSpawnTimer = repeat createZombies();
    return 1;
}

timer createZombies[50]()
{
    new rand = random(sizeof zombieSpawns);
    if(gSpawnedZombies < MAX_ZOMBIES)
    {
        new theNpc_, str[50];
        format(str, sizeof(str), "Zombie[%d]", MAX_PLAYERS-(gSpawnedZombies));
        theNpc_ = FCNPC_Create(str);
        FCNPC_Spawn(theNpc_, 241, zombieSpawns[rand][0], zombieSpawns[rand][1], zombieSpawns[rand][2]);
        FCNPC_SetWeapon(theNpc_, 1);
        FCNPC_SetHealth(theNpc_, 100);
        FCNPC_ApplyAnimation(theNpc_, "PED", "WALK_DRUNK", 4.1, 1, 1, 1, 0, 0);
        SetPlayerColor(theNpc_, 0xFF0000FF);
        gZombieTimer[theNpc_] = repeat zombieMove(theNpc_);
        IsAZombie[theNpc_] = true;
        gSpawnedZombies++;
    } else {
        stop gZombieSpawnTimer;
        print("Zombie Creation finished!");
    }
    return 1;
}

hook FCNPC_OnDeath(npcid, killerid, weaponid)
{
    gZombieIsAttack[npcid] = 0;
    ApplyActorAnimation(npcid, "PED", "BIKE_fall_off", 4.0, 0, 1, 1, 1, 0);
    CallLocalFunction("OnPlayerKillZombie", "ii", killerid, npcid);
    return 1;
}

timer zombieRespawn[500]()
{
    print("Respawning zombies!");
    foreach(new i : Player)
    {
        if(IsAZombie[i])
        {
            printf("Respawning zombie id %d", i);
            FCNPC_Respawn(i);
        }
    }
    return 1;
}

timer zombieMove[500](zombieid)
{
    new Float:x, Float:y, Float:z;
    if(FCNPC_IsDead(zombieid)) return 1;
    foreach(new i : Player)
    {
        GetPlayerPos(i, x, y, z);
        if(IsPlayerInRangeOfPoint(zombieid, 1.0, x, y, z))
        {
            FCNPC_ClearAnimations(zombieid);
            gZombieIsAttack[zombieid] = 2;
            FCNPC_MeleeAttack(zombieid, 100);
            break;
        }
        else if(IsPlayerInRangeOfPoint(zombieid, 10.0, x, y, z))
        {
            if(gZombieIsAttack[zombieid] == 2)
            {
                FCNPC_Stop(zombieid);
                FCNPC_StopAttack(zombieid);
            }
            gZombieIsAttack[zombieid] = 1;
            FCNPC_ClearAnimations(zombieid);
            FCNPC_GoTo(zombieid, x, y, z, FCNPC_MOVE_TYPE_RUN, 0.4, true);
            break;
        }
        else if(IsPlayerInRangeOfPoint(zombieid, 25.0, x, y, z))
        {
            if(gZombieIsAttack[zombieid] == 2)
            {
                FCNPC_Stop(zombieid);
                FCNPC_StopAttack(zombieid);
            }
            gZombieIsAttack[zombieid] = 1;
            FCNPC_ClearAnimations(zombieid);
            FCNPC_GotoPlayerEx(zombieid, i, 5, 5);
            break;
        }
        else
        {
            gZombieIsAttack[zombieid] = 0;
            FCNPC_ApplyAnimation(zombieid, "PED", "WALK_DRUNK", 4.1, 1, 1, 1, 0, 0);
        }
    }
    return 1;
}

hook FCNPC_OnUpdate(npcid)
{
    if(IsAZombie[npcid] && gZombieIsAttack[npcid] == 0)
    {
        FCNPC_ApplyAnimation(npcid, "PED", "WALK_DRUNK", 4.1, 1, 1, 1, 0, 0);
    }
    return 1;
}

stock FCNPC_GotoPlayerEx(npcid, playerid, Float:dist, Float:angle, movetype = FCNPC_MOVE_TYPE_RUN)
{
    new Float:xa, Float:ya, Float:za, Float:fa;
    GetPlayerPos(playerid, xa, ya, za);
    GetPlayerFacingAngle(playerid, fa);
    angle += fa;
    xa = (xa + dist * floatsin(-angle, degrees));
    ya = (ya + dist * floatcos(-angle, degrees));
    FCNPC_GoTo(npcid, xa, ya, za, movetype, 0.4, true);
    return 1;
}

hook FCNPC_OnRespawn(npcid)
{
    if(IsAZombie[npcid])
    {
        new rand = random(sizeof zombieSpawns);
        FCNPC_SetWeapon(npcid, 1);
        FCNPC_ApplyAnimation(npcid, "PED", "WALK_DRUNK", 4.1, 1, 1, 1, 0, 0);
        FCNPC_SetAmmo(npcid, 1);
        FCNPC_SetPosition(npcid, zombieSpawns[rand][0], zombieSpawns[rand][1], zombieSpawns[rand][2]);
    }
    return 1;
}