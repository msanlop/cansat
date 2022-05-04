#include "Temperature.h" // Used to send and recieve specific information from our sensor

Temperature::Temperature()
{};

double Temperature::getData()
{
    return sensor.readTempC();
};

void Temperature::begin()
{
    if (sensor.begin() == true) // Function to check if the sensor will correctly self-identify with the proper Device ID/Address
    {
      Serial.println("Begin");
    }
    else
    {
      Serial.println("Device failed to setup- Freezing code.");
    }
}
