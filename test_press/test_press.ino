#include <Wire.h>
#include "Pressure.h"

constexpr unsigned int SIZE(20);
double values[SIZE][4];

Pressure press;

void setup()
{
    Serial.begin(115200);    // Start serial communication at 115200 baud

    Wire.begin();
    Wire.setClock(400000);

    press.begin();
}

void loop()
{
    memset(values, 0, SIZE);
    
    for(auto& value : values)
    {
        press.getData(value);
        
        for ( int i = 0; i < SIZE; ++i ) 
        {
            // loop through columns of current row
            for ( int j = 0; j < 4; ++j )
            {
                Serial.print (values[ i ][ j ]);
                Serial.print (", ");
            }
            Serial.println(); // start new line of output
            delay(100);
        } 
        Serial.println();
        Serial.println();
        Serial.println();

        delay(100);
    }
    while(1){}
}
