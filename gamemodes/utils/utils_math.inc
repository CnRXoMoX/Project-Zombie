stock Float:frandom(Float:min, Float:max)
{
	new imin = floatround(min);
	return floatdiv(float(random((floatround(max)-imin)*100)+(imin*100)),100.0);
}

stock randomEx(min, max) {
    return (random(max)+min);
}