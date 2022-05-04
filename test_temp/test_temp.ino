#include <Wire.h>
#include "Temperature.h"

constexpr unsigned int SIZE(20);


Temperature temp;

void setup()
{
    Wire.begin();
    Serial.begin(115200);    // Start serial communication at 115200 baud
    Wire.setClock(400000);
    
    temp.begin();
}

void loop()
{
    double values[SIZE];
    unsigned int counter = 0; 
    while(1)
    {
        values[counter] = temp.getData();
        
        for(size_t i(0) ; i < SIZE ; i++)
        {
            Serial.print(values[i]);
            Serial.print(", ");
        }

        Serial.println();

        delay(50);
        
        counter++;
    }
}
