#include <SPI.h>
#include <LoRa.h>
#include <queue>
#include <list>

const int I2C_ADDRESS = 0; // TODO: define i2c address
const long FREQ = 869.500;

const int QUEUE_TRANSMIT_SIZE = 1; //TODO: define how big the msg and what field do we send

typedef list<unsigned char> message; //TODO: message sequence of bytes? or ex: int, int, double, float, ...?
queue<message> msgQueue;


//3 flashes
void ledsError(){
    digitalWrite(LED_BUILTIN, 1);
    delay(200);
    digitalWrite(LED_BUILTIN, 0);
    delay(200);
    digitalWrite(LED_BUILTIN, 1);
    delay(200);
    digitalWrite(LED_BUILTIN, 0);
    delay(200);
    digitalWrite(LED_BUILTIN, 1);
    delay(200);
    digitalWrite(LED_BUILTIN, 0);
    delay(1000);
};

void receiveEvent(int howMany) {
    Serial.print("I2C trasmists ");
    Serial.print(howMany);
    Serial.println("bytes");

    // message new_msg;
    while(1 <= Wire.available()) {
        unsigned char c = Wire.read(); //read 1 byte
    }
    // msgQueue.push_back(c);
}

boolean trasmitLoRa(list<message> msg){
    Serial.println("Sending packet");
    while(Lora.isTransmitting());
    LoRa.beginPacket();
    digitalWrite(RFM_SWITCH,0);
    // LoRa.print(...);
    LoRa.endPacket();
}



void setup() {
    Serial.begin(9600);
    while (!Serial);

    Wire.begin(I2C_ADDRESS)
    Wire.onReceive(receiveEvent);  //TODO: is this async?
    Serial.println("Wire setup finished");
    

    pinMode(RFM_TCX_ON,OUTPUT);
    pinMode(RFM_SWITCH,OUTPUT);
    pinMode(LED_BUILTIN,OUTPUT);
    LoRa.setPins(SS,RFM_RST,RFM_DIO0);
    if (!LoRa.begin(FREQ)) {
        Serial.println("Starting LoRa failed!");
        while (1){
            ledsError();
        };
    }
    Serial.println("Lora setup finished");
}

void loop() {
    digitalWrite(LED_BUILTIN,0);
    list<message> payload;
    while(msgQueue.size() < QUEUE_TRANSMIT_SIZE){
        digitalWrite(LED_BUILTIN,1);
        //TODO use a blocking queue instead
        //payload = msgQueue.pop(count)
    }
    trasmitLoRa(payload);
}