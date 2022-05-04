#include "Temperature.h" // Used to send and recieve specific information from our sensor

Temperature::Temperature()
{
    Wire.begin();
    Serial.begin(115200);    // Start serial communication at 115200 baud
    Wire.setClock(400000);

    if (sensor.begin() == true) // Function to check if the sensor will correctly self-identify with the proper Device ID/Address
    {
      Serial.println("Begin");
    }
    else
    {
      Serial.println("Device failed to setup- Freezing code.");
    }
};

double Temperature::getData()
{
    return sensor.readTempC();
};
