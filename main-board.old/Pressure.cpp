#include "Wire.h"            // Used to establish serial communication on the I2C bus
#include "Pressure.h"// Used to send and recieve specific information from our sensor

Pressure::Pressure()
{
    Wire.begin();
    
    if (mySensor.beginI2C() == false) //Begin communication over I2C
    {
        Serial.println("The sensor did not respond. Please check wiring.");
    }
};

void Pressure::getData(vector<double>& buff)
{
    buff_H.push_back(sensor.readFloatHumidity()));
    buff_P.push_back(sensor.readFloatPressure());
    buff_A.push_back(sensor.readFloatAltitudeMeters());
    buff_T.push_back(sensor.readTempC());
};