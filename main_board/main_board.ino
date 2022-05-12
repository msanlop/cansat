#include "Accelerometer.h"
#include "Pressure.h"
#include "Temperature.h"
#include <Wire.h>

#define LORA_MCU_ADDR 14 //CHANGE IN LORA MCU TOO
#define TEST_STRING "dafkdlakfjaksldjfl;dksajfl;kdsjaflkjaskldfjkdsfkjadslkjflkasdjflkjsaldkfjlsadkjflksdjaflkjdsalkfjldakjflkjasdlkfjlskadjflkjsalkfjalsjdfk"

constexpr unsigned int SIZE(4);
constexpr unsigned int DATA_NB(8);
constexpr int buzPin(11);

double buffer[SIZE][DATA_NB];
unsigned long time[SIZE];
String string_buffer = "";

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
    Serial.println("setup done");
}

void loop() {
    if(line == SIZE)
    {
      line = 0;
      column = 0;
    }
    getData();
    getData();
    getData();
    getData();
    make_string();
    // print_data();
    lora_transmit();
    Serial.println(string_buffer);
    //delay(idk) //best compromise between more data and battery consumption?
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
    acc.getData(&buffer[line][column]); //check if valid
   //TODO: 1 I2C call could be made instead of 3 here
    // buffer[line][column] = acc.getX();
    // column++;
    // buffer[line][column] = acc.getY();
    // column++;
    // buffer[line][column] = acc.getZ();
    // column+=3;

    column = 0;
    line++;
}

/**
 * @brief Transmit the string buffer over I2C to the LORA board. 
 * TODO: This might not be fast enough + max is 64 bytes...
 * 
 */
void lora_transmit()
{
  // const char *strin_c = string_buffer.c_str();
  Wire.beginTransmission(LORA_MCU_ADDR);
  Wire.write(string_buffer.c_str()); //TODO: max is 64 bytes, change this
  Wire.endTransmission();
  Serial.println("transmission done!");
}

/**
 * @brief Convert the data buffer to a String and update the string_buffer
 * 
 */
void make_string()
{
  string_buffer = "";
  for (int i = 0; i < SIZE; ++i) {
    string_buffer += String(time[i]) + ",";
    for (int j = 0; j < DATA_NB - 1; ++j) {
      string_buffer += String(buffer[i][j]) + ",";
    }
    string_buffer += String(buffer[i][DATA_NB - 1]);
    string_buffer += ";";
  }
}

void print_data()
{
    for (int i = 0; i < SIZE; ++i) {
        // loop through columns of current row
        Serial.print(time[i]);
        Serial.print(", ");
        for (int j = 0; j < DATA_NB; ++j) {
            Serial.print(buffer[i][j]);
            Serial.print(", ");
        }
        Serial.println(); // start new line of output
    }
}

void beep(){
  if(true) //change to actual mode == recovery
    while(1){ //keeps beeping each for 500
      tone(buzPin, 1568, 500);
      delay(500);
    }
}