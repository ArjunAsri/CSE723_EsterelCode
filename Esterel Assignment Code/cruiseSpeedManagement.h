//The type 'string' is defined as 'char*' in Esterel, hence passing a string by referenc  is 'char**'
//Aviod naming a function 'recv'
float saturateThrottle(float throttleIn, int saturate);
float regulateThrottle(int isGoingOn, float cruiseSpeed, float vehicleSpeed);
