#include <YSI_Coding\y_hooks>

enum E_VEHICLE_DATA
{
    vehicle_id,
    Float:vehicle_posX,
    Float:vehicle_posY,
    Float:vehicle_posZ,
    vehicle_tires,
    bool:vehicle_isDayzVeh,
    Float:vehicle_fuel,
    vehicle_engine,
    vehicle_state,
    Text3D:vehicle_text
};

enum E_VEHICLE_STATES 
{
    VEHICLE_STATE_DEAD = 0,
    VEHICLE_STATE_OFF,
    VEHICLE_STATE_ON
};

static
    vehicleData[MAX_VEHICLES][E_VEHICLE_DATA]
;

stock Vehicle_Create(modelid, Float:x, Float:y, Float:z, Float:rotation, color1, color2) {
    new tempid;
    tempid = CreateVehicle(modelid, Float:x, Float:y, Float:z, Float:rotation, color1, color2, -1);
    vehicleData[tempid][vehicle_text] = CreateDynamic3DTextLabel(""C_ORANGE"[VEHICLE]: "C_WHITE"Press "C_ORANGE"N"C_WHITE" to open inventory", -1, x, y, z, 50.0, .attachedvehicle = tempid);
    vehicleData[tempid][vehicle_id] = tempid;
    vehicleData[tempid][vehicle_posX] = x;
    vehicleData[tempid][vehicle_posY] = y;
    vehicleData[tempid][vehicle_posZ] = z;
    vehicleData[tempid][vehicle_isDayzVeh] = true;
    new Float:fuel = frandom(0.0, 100.0);
    vehicleData[tempid][vehicle_fuel] = fuel;
    new engine = random(1);
    new tires = random(4);
    vehicleData[tempid][vehicle_engine] = engine;
    vehicleData[tempid][vehicle_tires] = tires;
    CallLocalFunction("OnDayZVehicleCreate", "i", tempid);
    return tempid;
}

stock GetDayZVehiclePos(vehid, &Float:x, &Float:y, &Float:z) {
    x = vehicleData[tempid][vehicle_posX];
    y = vehicleData[tempid][vehicle_posY];
    z = vehicleData[tempid][vehicle_posZ];
}

stock IsDayZVehicle(vehicleid) {
    return vehicleData[vehicleid][vehicle_isDayzVeh];
}

hook OnVehicleDeath(vehicleid, killerid)
{
    if(IsDayZVehicle(vehicleid))
    {
        vehicleData[vehicleid][vehicle_posX] = 0.0;
        vehicleData[vehicleid][vehicle_posY] = 0.0;
        vehicleData[vehicleid][vehicle_posZ] = 0.0;
        vehicleData[vehicleid][vehicle_id] = INVALID_VEHICLE_ID;
        vehicleData[vehicleid][vehicle_isDayzVeh] = false;
        vehicleData[vehicleid][vehicle_fuel] = 0.0;
        vehicleData[vehicleid][vehicle_engine] = 0;
        vehicleData[vehicleid][vehicle_tires] = 0;
        if(IsValidDynamic3DTextLabel(vehicleData[vehicleid][vehicle_text])) {
            DestroyDynamic3DTextLabel(vehicleData[vehicleid][vehicle_text]);
        }
    }
    return 1;
}