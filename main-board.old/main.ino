#include <Wire.h>
#include "Accelerometer.h"
#include "Temperature.h"
#include "Pressure.h"
#include "Lora.h"
#include "Memory.h"
#include<ctime>

constexpr unsigned int SIZE(4);
double values[SIZE][9];

Pressure press;
Temperature temp;
Accelerometer acc;



void setup() {

    Serial.begin(115200);    // Start serial communication at 115200 baud

    Wire.begin();
    Wire.setClock(400000);

    press.begin();
    temp.begin();
    acc.begin();

    comms.confirmSetup(millis());
    //check cansat status with altitude?
    while(!accel.isFlying()) {
        //LED state to make sure correct mode
        delay(100)
    } 
    comms.confirmLaunch(millis());
}

void loop() {
    size_t lastWritten = 0;
    unsigned long lastMemWrite, lastdownlink = millis();

    while(accel.isFlying()){
        
        //poll all sensors
        deltas.push_back(millis());
        if(writeToMemoryNow() || downlinkNow()){
            //start write from where last time ended
            mem.writeBuff(values, deltas, lastWritten);
            lastWritten = deltas.size()
        }
        if (downlinkNow()){
            coms.transferData(values, deltas);
            lastWriten = 0;
            clearBuffers();
        }
    }

    while(!accel.isFlying()){
        //turn on buzzer
        //do gps stuff
        //transmit location
    }
}