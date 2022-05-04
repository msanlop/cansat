#ifndef TEMPERATURE_H
#define TEMPERATURE_H

#include <Wire.h>
#include "SparkFun_TMP117.h"

class Temperature
{
    // private:

    public:
        TMP117 sensor;
        Temperature();
        double getData();
        void begin();
};

#endif
