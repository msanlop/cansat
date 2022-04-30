void setup() {
//   Setup loraid access
  Serial.begin(115200);
  while(!Serial); //wait for connection?
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.println("Finished setup");
}

void loop() {
  // Check interval overflow
  int seconds_passed = 0;
  const int LOW_TIME = 200;
  char buf[1024];
  while(1){
    digitalWrite(LED_BUILTIN, HIGH);
    delay(1000-LOW_TIME);
    digitalWrite(LED_BUILTIN, LOW);
    sprintf(buf, "Still here ! %0d s have passed now", seconds_passed);
    Serial.println(buf);
    delay(LOW_TIME);
    // Serial.println("Hello still here");
    seconds_passed++;
  };
}