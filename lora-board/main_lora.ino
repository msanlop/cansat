#include <LoRa.h>
#include <Wire.h>

#define I2C_ADDRESS 14 // CHANGE IN MAIN MCU TOO

#define SPREADING_FACTOR 7 //lower == higher bit rate but less range

const long FREQ = 869.500;

int i_index = 0;

String str_buf = "";

const int QUEUE_TRANSMIT_SIZE =
    1; // TODO: define how big the msg and what field do we send

#define msg126B "135877722,-0.20,-0.84,-0.54,84.48,59245.96,4302.85,22.08,25.94,135877722,-0.20,-0.84,-0.54,84.48,59245.96,4302.85,22.08,25.94"


#define msg247B                                                                \
    "135877722,-0.20,-0.84,-0.54,84.48,59245.96,4302.85,22.08,25.94,"          \
    "135877722,-0.20,-0.84,-0.54,84.48,59245.96,4302.85,22.08,25.94,"          \
    "135877722,-0.20,-0.84,-0.54,84.48,59245.96,4302.85,22.08,25.94,"          \
    "135877722,-0.20,-0.84,-0.54,84.48,59245.96,4302.85,22.08"

unsigned long old_time = 0;
unsigned long delta = 0;

boolean trasmitLoRa() {
    Serial.print("Sending packet : ");
    Serial.println(i_index);
    // while (LoRa.isTransmitting()){}; //private...
    LoRa.beginPacket();
    LoRa.print(msg247B);
    // Serial.println("print packet testest");
    LoRa.endPacket();
    i_index++;
}

//IMPORTANT: Set serial buffer to 256
void receiveEvent(int howMany) {
    digitalWrite(LED_BUILTIN, 0);
    Serial.print(howMany);
    Serial.println(" incoming bytes.");

    str_buf = "";
    // message new_msg;
    while(1 <= Wire.available()) {
      char c = Wire.read();
      str_buf += c; //read 1 byte
    }
    Serial.print("Received : ");
    Serial.println(str_buf);
    digitalWrite(LED_BUILTIN, 1);
}

void setup() {
    //   Setup loraid access
    Serial.begin(115200);
    while (!Serial);


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
    delay(50);
    //add led msg for normal operation
}
