#include <Wire.h>
#include "Accelerometer.h"
#include <math.h> 

Accelerometer::Accelerometer()
{
    if(!sensor.begin()) 
        Serial.println("Could not communicate with the the KX13X.");
    else 
        Serial.println("Accelerometer ready!");
    
    if( !kxAccel.initialize(DEFAULT_SETTINGS))
        Serial.println("Could not initialize the chip.");
    else
        Serial.println("Initialized...");
    data = {0.0, 0.0, 0.0};
}

void Accelerometer::getData(vector<double> buff){
    myData = kxAccel.getAccelData();
    buff.push_back(myData.xData);
    buff.push_back(myData.yData);
    buff.push_back(myData.zData);
};

double Accelerometer::getAcceleration(outputData& myData){
    double x = myData.xData;
    double y = myData.yData;
    double z = myData.zData;
    
    return sqrt(x*x + y*y + z*y);
}

bool Accelerometer::isFlying(){
    if(getAcceleration < 10)
        return false;
    else 
        return true;
}