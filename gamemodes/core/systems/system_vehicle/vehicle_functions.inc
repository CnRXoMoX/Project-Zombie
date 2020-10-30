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
    vehicle_state
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
}

stock GetDayZVehiclePos(vehid, &Float:x, &Float:y, &Float:z) {
    x = vehicleData[tempid][vehicle_posX];
    y = vehicleData[tempid][vehicle_posY];
    z = vehicleData[tempid][vehicle_posZ];
}

stock IsDayZVehicle(vehicleid) {
    return vehicleData[vehicleid][vehicle_isDayzVeh];
}