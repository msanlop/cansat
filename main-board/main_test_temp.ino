#include <Wire.h>
#include "Temperature.h"

Temperature temp;

void loop()
{
    vector<double> values;

    while(1)
    {
        temp.getData(values);
        
        for(size_t i(0) ; i < values.size() ; i++)
        {
            Serial.println(values[i]"," );
        }

        delay(50);
    }
}