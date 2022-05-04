#include <Wire.h>
#include "Temperature.h"

constexpr unsigned int SIZE(20);


Temperature temp;

void setup()
{
    Serial.begin(115200);    // Start serial communication at 115200 baud
    Serial.println("serial begin done");

    Wire.begin();
    Serial.println("wire begin done");
    Wire.setClock(400000);
    Serial.println("wire clock done");
    pinMode(LED_BUILTIN, OUTPUT);
    Serial.println("Wire clock set");
    Serial.println("Led setup done");
    
    // temp.begin();
    temp.sensor.begin(0x48, Wire);
}

void loop()
{
    double values[SIZE];
    unsigned int counter = 0; 
    while(1)
    {
        digitalWrite(LED_BUILTIN, 1);
        // values[counter] = temp.getData();
        
        for(size_t i(0) ; i < SIZE ; i++)
        {
            Serial.print(values[i]);
            Serial.print(", ");
        }

        Serial.println();

        delay(50);
        
        counter++;
        digitalWrite(LED_BUILTIN, 0);
    }
}
