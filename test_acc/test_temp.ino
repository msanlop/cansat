#include <Wire.h>
#include "Accelerometer.h"

constexpr unsigned int SIZE(20);

Accelerometer acc;

void setup()
{
    while(!Serial){
        delay(50);
    }

    Serial.begin(115200);
    Serial.println("Welcome.");
    Wire.begin();
    acc = new Accelerometer();
}
void loop()
{
    double data[SIZE];

    unsigned int counter = 0; 
    acc.getData(data);
    Serial.println(acc);
    delay(20);
        
    counter++;
}
