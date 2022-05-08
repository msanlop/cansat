#include <LoRa.h>
#include <SPI.h>

const int I2C_ADDRESS = 0; // TODO: define i2c address
const long FREQ = 869.500;

int i_index = 0;

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

void setup() {
    //   Setup loraid access
    Serial.begin(115200);
    while (!Serial){}; // wait for connection?

    pinMode(RFM_TCX_ON,OUTPUT);
    pinMode(RFM_SWITCH,OUTPUT);
    pinMode(LED_BUILTIN,OUTPUT);
    LoRa.setPins(SS,RFM_RST,RFM_DIO0);
    if (!LoRa.begin(FREQ)) {
        Serial.println("Starting LoRa failed!");
        Serial.println("Stopping exec");
        while (1);
    }
    // LoRa.setSpreadingFactor(6); //faster transmit rate

    Serial.println("Finished setup");
}

void loop() {
    // Check interval overflow
    old_time = millis();
    digitalWrite(LED_BUILTIN, HIGH);
    trasmitLoRa();
    digitalWrite(LED_BUILTIN, LOW);
    delta = millis() - old_time;
    Serial.print("Transmission took : ");
    Serial.print(delta);

    delay(400);
}
