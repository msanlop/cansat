#include <LoRa.h>
#include <Wire.h>

#define I2C_ADDRESS 14 // CHANGE IN MAIN MCU TOO

#define SPREADING_FACTOR 7 //lower == higher bit rate but less range
#define STRING_MAX_LEN 63

const long FREQ = 869.500;

constexpr unsigned int MEM_SIZE(420);

#define STRING_MAX_LEN 63
char data_mem[MEM_SIZE][STRING_MAX_LEN + 1];
int mem_counter = 0;

int packet_nb = 0;

#define MEM_SAVE_INTERVAL 2500
unsigned long t0_save_ram = millis();


String str_buf = "";

unsigned long old_time = 0;
unsigned long delta = 0;

void transmit_string_buff() {
    Serial.print("Sending packet : ");
    Serial.println(packet_nb);
    // while (LoRa.isTransmitting()){}; //private...
    LoRa.beginPacket();
    LoRa.print(str_buf);
    // Serial.println("print packet testest");
    LoRa.endPacket();
    packet_nb++;
}

//
/**
 * @brief IMPORTANT: Set serial buffer to 256
 * On receive construct string, transmit packet and save a data point to RAM if needed
 * 
 * @param howMany 
 */
void receiveEvent(int howMany) {
    digitalWrite(LED_BUILTIN, 0);
    Serial.print(howMany);
    Serial.println(" incoming bytes.");

    str_buf = "";
    while(1 <= Wire.available()) {
      char c = Wire.read();
      str_buf += c; //read 1 byte
    }
    Serial.print("Received : ");
    Serial.println(str_buf);
    unsigned long delta = millis() - t0_save_ram;
    if (delta >= MEM_SAVE_INTERVAL && mem_counter<MEM_SIZE && str_buf.length() > 3 * STRING_MAX_LEN + 3){
        //record third datapoint to maximize coverage between MCUs
        strncpy(data_mem[mem_counter++], str_buf.c_str() + 2*STRING_MAX_LEN, STRING_MAX_LEN);
        t0_save_ram = millis();
    }
    transmit_string_buff();
    digitalWrite(LED_BUILTIN, 1);
}

/**
 * @brief Prints data in RAM to serial
 * 
 */
void print_data(){
    Serial.println();
    Serial.println();
    Serial.print("Printing ram data after ms : ");
    Serial.println(millis());
    for (int i = 0; i < mem_counter && i < MEM_SIZE; ++i) {
        Serial.println(data_mem[i]);
    }
    Serial.println();
    Serial.println();
}

void idle_leds(){
  digitalWrite(LED_BUILTIN, 1);
  delay(500);
  digitalWrite(LED_BUILTIN, 0);
  delay(500);
}


void setup() {
    //   Setup loraid access
    Serial.begin(115200);


    Wire.begin(I2C_ADDRESS);
    Wire.onReceive(receiveEvent);  //TODO: is this async?
    Serial.println("Wire setup finished");


    //Lora setup
    pinMode(RFM_TCX_ON,OUTPUT);
    pinMode(RFM_SWITCH,OUTPUT);
    pinMode(LED_BUILTIN,OUTPUT);
    LoRa.setPins(SS,RFM_RST,RFM_DIO0);
    if (!LoRa.begin(FREQ)) {
        Serial.println("Starting LoRa failed!");
        Serial.println("Stopping exec");
        //add led msg
        while (1);
    }
    
    // LoRa.setSpreadingFactor(SPREADING_FACTOR);
    // Serial.println(LoRa.getSpreadingFactor()); //default is 7
    Serial.println("Finished setup");
}

void loop() {
    print_data();
    idle_leds();
}
