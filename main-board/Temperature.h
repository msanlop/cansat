#pragma once

#include <Wire.h>   
#include <SparkFun_Qwiic_KX13X.h>
#include <SparkFun_TMP117.h>

class Temperature
{
    private:
        TMP117 sensor;

    public:
        Temperature();
        void getData(vector<double>& buff);
};