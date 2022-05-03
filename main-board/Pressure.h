#pragma once

#include <Wire.h>   
#include <SparkFun_Qwiic_KX13X.h>
#include <SparkFunBME280.h>

class Pressure
{
    private:
        BME280 Sensor;

    public:
        Pressure();
        void getData(vector<double>& buff_H, vector<double>& buff_P, vector<double>& buff_A, vector<double>& buff_T);
};