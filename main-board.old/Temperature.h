#ifndef TEMPERATURE_H
#define TEMPERATURE_H

#include <Wire.h>
#include "SparkFun_TMP117.h"

class Temperature
{
    private:
    TMP117 sensor;

    public:
        Temperature();
        double getData();
        void begin();
};

#endif
