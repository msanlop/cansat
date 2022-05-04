#include <Wire.h>
#include "Pressure.h"

constexpr unsigned int SIZE(20);

Pressure press;

void setup()
{
  // Set clock speed to be the fastest for better communication (fast mode)
}

void loop()
{
    double values[SIZE][4];
    unsigned int counter = 0; 
    while(1)
    {
        press.getData(values[counter]);
        
        for ( int i = 0; i < 4; ++i ) 
        {
            // loop through columns of current row
            for ( int j = 0; j < SIZE; ++j )
            {
                Serial.print (values[ i ][ j ] );
                Serial.print ('\r') ; // start new line of output
            }
        } 

        delay(50);
        
        counter++;
    }
}
