#include "Pressure.h" // Used to send and recieve specific information from our sensor

Pressure::Pressure()
{
}

double Pressure::getHumidity()
{
    return sensor.readFloatHumidity();
}

double Pressure::getPressure()
{
    return sensor.readFloatPressure();
}

double Pressure::getAltitude()
{
    return sensor.readFloatAltitudeMeters();
}

void Pressure::begin()
{
    if (sensor.beginI2C() == false) //Begin communication over I2C
    {
        Serial.println("The sensor did not respond. Please check wiring.");
    }
}
