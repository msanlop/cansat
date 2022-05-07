#pragma once

#include "SparkFun_Qwiic_KX13X.h"
class Accelerometer
{
    private:
        QwiicKX132 sensor; //TODO: does this construct on Accelerometer construction?
        outputData data;

    public:
        void begin();
        double getData(double value[3]);
        double getX();
        double getY();
        double getZ();
        bool isFlying();
        double getAcceleration();
};
