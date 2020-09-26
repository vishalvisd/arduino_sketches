#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

const char* ssid = "Tenda_435C38";
const char* password = "visdnick";

int relay1Pin = 2; // GPIO2 of ESP8266
int relay0Pin = 0; // GPI00 of ESP8266


WiFiServer server(80);

void setup() {
  Serial.begin(115200);

  pinMode(relay1Pin, OUTPUT);
  pinMode(relay0Pin, OUTPUT);
  digitalWrite(relay1Pin, LOW);
  digitalWrite(relay0Pin, LOW);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
  }
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    WiFiClient client = server.available();

    if (client) {
      
    }

    http.begin("http://visdiot.appspot.com/getinstruction");
    int httpCode = http.GET();

    if (httpCode > 0){
      String ins = http.getString();
//      const char* ins = instruction.c_str();
      Serial.print("instruction:");
      Serial.println(ins);  
      if (ins.indexOf("00") != -1){
        digitalWrite(relay1Pin, LOW);
        digitalWrite(relay0Pin, LOW);
        Serial.println("ins: 00");
      } else if (ins.indexOf("01") != -1){
        digitalWrite(relay1Pin, LOW);
        digitalWrite(relay0Pin, HIGH);
        Serial.println("ins: 01");
      } else if (ins.indexOf("10") != -1){
        digitalWrite(relay1Pin, HIGH);
        digitalWrite(relay0Pin, LOW);
        Serial.println("ins: 10");
      } else if (ins.indexOf("11") != -1){
        digitalWrite(relay1Pin, HIGH);
        digitalWrite(relay0Pin, HIGH);
        Serial.println("ins: 11");
      }
      
//      Serial.print("ins:");
//      Serial.println(ins);   
    }
    http.end();
  }
  delay(1000);
}
