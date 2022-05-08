#include <Wire.h>
#include "Accelerometer.h"
#include <math.h> 

Accelerometer::Accelerometer()
{
    if(!sensor.begin()) 
        Serial.println("Could not communicate with the the KX13X.");
    else 
        Serial.println("Accelerometer ready!");
    
    if( !sensor.initialize(DEFAULT_SETTINGS))
        Serial.println("Could not initialize the chip.");
    else
        Serial.println("Initialized...");
    data = {0.0, 0.0, 0.0};
}

void Accelerometer::getData(vector<double>& buff_X, vector<double>& buff_Y, vector<double>& buff_Z);{
    outputData myData = sensor.getAccelData();
    buff_X.push_back(myData.xData);
    buff_Y.push_back(myData.yData);
    buff_Z.push_back(myData.zData);
};

double Accelerometer::getAcceleration(){
    outputData myData = sensor.getAccelData();
    double x = myData.xData;
    double y = myData.yData;
    double z = myData.zData;
    
    return sqrt(x*x + y*y + z*y);
}

//TO TEST!!!!!!!!!!!!
bool Accelerometer::isFlying(){
    outputData myData = sensor.getAccelData();
    if(getAcceleration(myData) < 10)
        return false;
    else 
        return true;
}