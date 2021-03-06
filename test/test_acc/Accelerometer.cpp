#include <Wire.h>
#include "Accelerometer.h"
#include <math.h> 

QwiicKX132 sensor;

void Accelerometer::begin()
{
    if(!sensor.begin()) 
        Serial.println("Could not communicate with the the KX13X.");
    else 
        Serial.println("Accelerometer ready!");
    
    if( !sensor.initialize(DEFAULT_SETTINGS))
        Serial.println("Could not initialize the chip.");
    else
        Serial.println("Initialized...");
}

double Accelerometer::getX(){
    outputData myData = sensor.getAccelData();
    Serial.print("X : ");
    Serial.println(myData.xData);
    return myData.xData;
}

double Accelerometer::getY(){
    outputData myData = sensor.getAccelData();
    Serial.print("Y : ");
    Serial.println(myData.yData);
    return myData.yData;
}

double Accelerometer::getZ(){
    outputData myData = sensor.getAccelData();
    Serial.print("Z : ");
    Serial.println(myData.zData);
    return myData.zData;
}

void Accelerometer::getData(double values[]){
    outputData myData = sensor.getAccelData();
    values[0] = myData.xData;
    (values)[1] = myData.yData;
    (values)[2] = myData.zData;
}
double Accelerometer::getAcceleration(){
    outputData myData = sensor.getAccelData();
    double x = myData.xData;
    double y = myData.yData;
    double z = myData.zData;
    double acc = sqrt((x*x) + (y*y) + (z*z));
    return acc;
}

bool Accelerometer::isFlying(){
    outputData myData = sensor.getAccelData();
    if(getAcceleration() < 3){
        Serial.println("Too slow, go faster!!");
        return false;
    }
    else{ 
        Serial.println("Fast!!");
        return true;
    }
}