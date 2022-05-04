#include <Wire.h>
#include "Temperature.h"

constexpr unsigned int SIZE(20);

Temperature temp;

void setup()
{
  
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
            Serial.println(values[i] );
        }

        delay(50);
        
        counter++;
    }
}
