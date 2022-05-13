#include <Wire.h>
#include "Temperature.h"

constexpr unsigned int SIZE(20);
double values[SIZE];

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
    memset(values, 0, SIZE);
    
    for(auto& value : values)
    {
        value = temp.getData();
        
        for(size_t j(0) ; j < SIZE ; j++)
        {
            Serial.print(values[j]);
            Serial.print(", ");
        }
        
        Serial.println();
        delay(100);
    }
    while(1){}
}
