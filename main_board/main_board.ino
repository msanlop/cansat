#include "Accelerometer.h"
#include "Pressure.h"
#include "Temperature.h"
#include <Wire.h>

#define LORA_MCU_ADDR 14 //CHANGE IN LORA MCU TOO

enum FLIGHT_STAGE {STAGE_IDLE, STAGE_RECORD, STAGE_RECOVERY};
FLIGHT_STAGE current_stage = STAGE_IDLE;

unsigned long record_stage_time = 0.0;
unsigned long recovery_stage_time = 0.0;

// #define ZERO_ALTITUDE //IDK???

constexpr unsigned int SIZE(4);
constexpr unsigned int DATA_NB(7);
constexpr int buzPin(11);

constexpr unsigned int MEM_SIZE(2950);

// double data_mem[MEM_SIZE][DATA_NB];
#define MEM_SAVE_INTERVAL 1000 // in ms
#define STRING_MAX_LEN 63
char data_mem[MEM_SIZE][STRING_MAX_LEN + 1];
int mem_counter = 0;

double buffer[SIZE][DATA_NB];
enum BUFF_ID {TEMP, HUM, PRES, ALT, ACCEL};

unsigned long time_buffer[SIZE];
String string_buffer = "";

size_t line = 0;
size_t column =0;

Temperature temp;
Pressure press;
Accelerometer acc;

double altitude_zero;
//altitude to start recording at
double altitude_rec;


void setup() {
    Serial.begin(115200); // Start serial communication at 115200 baud
    Wire.begin();
    Wire.setClock(400000);

    temp.begin();
    press.begin();
    acc.begin();
    Serial.println("setup done");

    pinMode(LED_BUILTIN,OUTPUT);


    altitude_zero = press.getAltitude();
    altitude_rec = altitude_zero + 250;
}


void loop() {
  //IDLE STAGE
  while(idle_stage()){
    idle_leds();
  }

  //RECORD STAGE
  record_stage_time = millis();
  long t0 = millis();
  while(record_stage()){
    getData();
    long delta = millis() - t0;  
    
    //transmit buffer
    if (line == SIZE){
      line = 0;
      make_string();

      //save 1 reading to RAM
      if(delta >= MEM_SAVE_INTERVAL && mem_counter<MEM_SIZE){
        strncpy(data_mem[mem_counter++], string_buffer.c_str(), STRING_MAX_LEN);
        t0 = millis();
      }
      lora_transmit();
    }
  }

  //RECOVERY STAGE
  recovery_stage_time = millis();
  tone(buzPin, 1568, 500); // activate once or in loop??
  while(current_stage == STAGE_RECOVERY){
    print_data();
    recovery_leds(); //2 second delay
  }
}
    //delay(idk) //best compromise between more data and battery consumption?

void getData() {
    time_buffer[line] = millis();
    buffer[line][TEMP] = temp.getData();
    buffer[line][HUM] = press.getHumidity();
    buffer[line][PRES] = press.getPressure();
    buffer[line][ALT] = press.getAltitude();
    acc.getData(&buffer[line][ACCEL]); //check if equivalent to below
    // buffer[line][column] = acc.getX();
    // column++;
    // buffer[line][column] = acc.getY();
    // column++;
    // buffer[line][column] = acc.getZ();
    // column+=3;
    line++;
}

//true if cansat is above landing height 
//and TODO: while accelerometer data is active
bool record_stage(){
  return (current_stage == STAGE_RECORD && 
    (press.getAltitude() >= altitude_zero + 5));
    // + condition accelerometer is still ?
}

//true if cansat is under record height threshold
bool idle_stage(){
  return (current_stage == STAGE_IDLE && 
    press.getAltitude() < altitude_rec);
}

/**
 * @brief Transmit the string buffer over I2C to the LORA board. 
 * 
 */
void lora_transmit()
{
  // const char *strin_c = string_buffer.c_str();
  Wire.beginTransmission(LORA_MCU_ADDR);
  Wire.write(string_buffer.c_str());
  uint8_t tx_res = Wire.endTransmission();
  Serial.print("transmission done. Err code : ");
  Serial.println(tx_res);
  Serial.println(string_buffer);
}

/**
 * @brief Convert the data buffer to a String and update the string_buffer
 * 
 */
void make_string()
{
  string_buffer = "";
  for (int i = 0; i < SIZE; ++i) {
    string_buffer += String(time_buffer[i]) + ",";
    for (int j = 0; j < DATA_NB - 1; ++j) {
      string_buffer += String(buffer[i][j]) + ",";
    }
    string_buffer += String(buffer[i][DATA_NB - 1]);
    string_buffer += ";";
  }
  
}

/**
 * @brief Prints the data saved in RAM to serial
 * 
 */
void print_data()
{
  //PRINT BUFFER
    // for (int i = 0; i < SIZE; ++i) {
    //     // loop through columns of current row
    //     Serial.print(time_buffer[i]);
    //     Serial.print(", ");
    //     for (int j = 0; j < DATA_NB; ++j) {
    //         Serial.print(buffer[i][j]);
    //         Serial.print(", ");
    //     }
    //     Serial.println(); // start new line of output
    // }

  for (int i = 0; i < mem_counter; ++i) {
      Serial.print(data_mem[i]);
      Serial.println();
  }
  Serial.println();
  Serial.println();

}

void beep(){
  if(true) //change to actual mode == recovery
    while(1){ //keeps beeping each for 500
      tone(buzPin, 1568, 500);
      delay(500);
    }
}




//2 flashes every second pattern
void idle_leds(){
  digitalWrite(LED_BUILTIN, 1);
  delay(300);
  digitalWrite(LED_BUILTIN, 0);
  delay(300);
  digitalWrite(LED_BUILTIN, 1);
  delay(300);
  digitalWrite(LED_BUILTIN, 0);
  delay(100);
}

//3 quick flashes / 2 second
void recovery_leds(){
  int period = 1000;
  digitalWrite(LED_BUILTIN, 1);
  delay(period/6);
  digitalWrite(LED_BUILTIN, 0);
  delay(period/6);
  digitalWrite(LED_BUILTIN, 1);
  delay(period/6);
  digitalWrite(LED_BUILTIN, 0);
  delay(period/6);
  digitalWrite(LED_BUILTIN, 1);
  delay(period/6);
  digitalWrite(LED_BUILTIN, 0);
  delay(period/6 + period);
}