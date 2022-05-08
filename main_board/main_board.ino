#include "Accelerometer.h"
#include "Pressure.h"
#include "Temperature.h"
#include <Wire.h>

constexpr unsigned int SIZE(4);
constexpr unsigned int DATA_NB(8);

double buffer[SIZE][DATA_NB];
unsigned long time[SIZE];

size_t line = 0;
size_t column =0;

int counter = 0;

Temperature temp;
Pressure press;
Accelerometer acc;

void setup() {
    Serial.begin(115200); // Start serial communication at 115200 baud
    Wire.begin();
    Wire.setClock(400000);

    temp.begin();
    press.begin();
    acc.begin();
}

void loop() {

    if(line == SIZE)
    {
      line = 0;
      column = 0;
    }
    Serial.println(millis());
    getData();
    print_data();
}

void getData() {
    time[line] = millis();
  
    buffer[line][column] = 0; //mode
    column++;
    buffer[line][column] = temp.getData();
    column++;
    buffer[line][column] = press.getHumidity();
    column++;
    buffer[line][column] = press.getPressure();
    column++;
    buffer[line][column] = press.getAltitude();
    column++;
    buffer[line][column] = acc.getX();
    column++;
    buffer[line][column] = acc.getY();
    column++;
    buffer[line][column] = acc.getZ();
    column++;

    column = 0;
    line++;
}

void print_data()
{
    for (int i = 0; i < SIZE; ++i) {
        // loop through columns of current row
        //Serial.print(time[i]);
        //Serial.print(", ");
        for (int j = 0; j < DATA_NB; ++j) {
            Serial.print(buffer[i][j]);
            Serial.print(", ");
        }
        Serial.println(); // start new line of output
        delay(100);
    }
    Serial.println();
    Serial.println();
    Serial.println();

    delay(100);
}
