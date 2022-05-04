#include <Wire.h>
#include "Accelerometer.h"

constexpr unsigned int SIZE(1000);

Accelerometer acc;
double xvalues[SIZE];
double yvalues[SIZE];
double zvalues[SIZE];
int count(0);

void setup()
{
    Serial.begin(115200);
    Serial.println("Welcome.");
    Wire.begin();
    acc.begin();
}
void loop()
{
    for(int i = 0; i < 3 && count < SIZE; i++){
        xvalues[count] = acc.getX();
        yvalues[count] = acc.getY();
        zvalues[count] = acc.getZ();
    }
    acc.getAcceleration();
    acc.isFlying();
    Serial.println("-------------------------------------------------------");
    count++;
    //acc.getData(data);
    delay(1000);
}
