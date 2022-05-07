#include <Wire.h>
#include "Accelerometer.h"

constexpr unsigned int SIZE(1000);
double values[SIZE][3];

Accelerometer acc;


void setup()
{
    Serial.begin(115200);
    Serial.println("Welcome.");
    Wire.begin();
    acc.begin();
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
            for ( int j = 0; j < 3; ++j )
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

/**
 * @brief 
 * double xvalues[SIZE];
    double yvalues[SIZE];
    double zvalues[SIZE];
    int count(0);
    
 * for(int i = 0; i < 3 && count < SIZE; i++){
        xvalues[count] = acc.getX();
        yvalues[count] = acc.getY();
        zvalues[count] = acc.getZ();
    }
    acc.getAcceleration();
    acc.isFlying();
    Serial.println("-------------------------------------------------------");
    count++;
    //acc.getData(data);
    delay(1000);
 * 
 */
