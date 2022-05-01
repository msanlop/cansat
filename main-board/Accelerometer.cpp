#include <Wire.h>
#include "Accelerometer.h"

Accelerometer::Accelerometer()
{
    sensor.begin();
    data = {0.0, 0.0, 0.0};
};

double Accelerometer::getData(vector<double> buff){
    buff.push_back(data);
};

bool Accelerometer::isFlying(){
    return false;
}