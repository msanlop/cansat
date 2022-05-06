#include "Pressure.h" // Used to send and recieve specific information from our sensor

Pressure::Pressure()
{
}

void Pressure::getData(double values[4])
{
    values[0] = sensor.readFloatHumidity();
    values[1] = sensor.readFloatPressure();
    values[2] = sensor.readFloatAltitudeMeters();
    values[3] = sensor.readTempC();
}

void Pressure::begin()
{
    if (sensor.beginI2C() == false) //Begin communication over I2C
    {
        Serial.println("The sensor did not respond. Please check wiring.");
    }
}
