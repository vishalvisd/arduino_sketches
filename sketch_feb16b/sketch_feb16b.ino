#include <SoftwareSerial.h>

SoftwareSerial esp8266(7,8); //rx, tx
bool isRelayOn = false;

void setup() {
  Serial.begin(9600); 
  esp8266.begin(9600);
}

void loop() {
  String isBoradRelayOn = esp8266.readString();
  Serial.println("received" + isBoradRelayOn);
  if (isRelayOn){
     esp8266.write("r1c");
     Serial.println("sent r1c");
  } else {
     esp8266.write("r0c");
     Serial.println("sent r0c");
  }
  isRelayOn = !isRelayOn;
  Serial.flush();
  delay(1000);
}
