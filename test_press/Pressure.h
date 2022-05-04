#ifndef PRESSURE_H
#define PRESSURE_H

#include <Wire.h>
#include "SparkFunBME280.h"

class Pressure
{
    private:
        BME280 sensor;

    public:
        Pressure();
        void getData(double values[4]);
};

#endif
