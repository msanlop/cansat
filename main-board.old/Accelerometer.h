#pragma once

#include "SparkFun_Qwiic_KX13X.h"

class Accelerometer
{
    private:
        QwiicKX132 sensor; //TODO: does this construct on Accelerometer construction?
        outputData data;

    public:
        Accelerometer();
        void getData(vector<double>& buff_X, vector<double>& buff_Y, vector<double>& buff_Z);
        bool isFlying();
        double getAcceleration(outputData& myData);
}