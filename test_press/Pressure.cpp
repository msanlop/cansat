#include "Pressure.h" // Used to send and recieve specific information from our sensor

Pressure::Pressure()
{
    Wire.begin();
    Serial.begin(115200);
    Serial.println("Reading basic values from BME280");
    
    if (sensor.beginI2C() == false) //Begin communication over I2C
    {
        Serial.println("The sensor did not respond. Please check wiring.");
    }
};

void Pressure::getData(double values[4])
{
    values[0] = sensor.readFloatHumidity();
    values[1] = sensor.readFloatPressure();
    values[2] = sensor.readFloatAltitudeMeters();
    values[3] = sensor.readTempC();
};
