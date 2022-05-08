#include "Accelerometer.h"
#include "Pressure.h"
#include "Temperature.h"
#include <Wire.h>

constexpr unsigned int SIZE(1);
constexpr unsigned int DATA_NB(4);

double buffer[SIZE][DATA_NB];
size_t index_i = 0;

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
    getData();
    print_data();
}

void getData() {
    Serial.println("getting data");
    buffer[0][index_i] = (double)millis();
    index_i++;
    buffer[0][index_i] = temp.getData();
    index_i++;
    // press.getData(buffer[0][index_i]);
    // index_i += 4;
}

void print_data() {
    Serial.println("printing data");

    for (int i = 0; i < SIZE; ++i) {
        // loop through columns of current row
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