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
        double getHumidity();
        double getPressure();
        double getAltitude();
        void begin();
};

#endif
