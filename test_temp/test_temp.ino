#include <Wire.h>
#include "Temperature.h"
#include "SparkFun_TMP117.h"

constexpr unsigned int SIZE(20);

Temperature temp;

void setup()
{
    Serial.begin(115200);    // Start serial communication at 115200 baud

    Wire.begin();
    Wire.setClock(400000);
    
    temp.begin();
}

void loop()
{
    double values[SIZE];
    
    for(size_t i(0) ; i < SIZE ; i++)
    {
        values[i] = temp.getData();
        
        for(size_t j(0) ; j < SIZE ; j++)
        {
            Serial.print(values[j]);
            Serial.print(", ");
        }
        
        Serial.println();
        delay(50);
    }
}
