#include <Wire.h>
#include "Accelerometer.h"
#include "Lora.h"
#include "Memory.h"
#include<ctime>


Accelerometer accel;
Lora comms;
Memory mem;

void setup() {
    comms.confirmSetup(millis());
    //check cansat status with altitude?
    while(!accel.isFlying()) {
        //LED state to make sure correct mode
        delay(100)
    } 
    comms.confirmLaunch(millis());
}

void loop() {
    vector<vector<double>> values;
    vector<unsigned long> deltas;
    size_t lastWritten = 0;
    unsigned long lastMemWrite, lastdownlink = millis();

    while(accel.isFlying()){
        accel.getData(values);
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