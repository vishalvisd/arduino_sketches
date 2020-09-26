//This run on ESP8266 and subscribe to a pubnub channel for instruction. Based on the instruction, it operates the solid state relays. The result of the instruction execution will be published back to the specifed pubnub channel.
//Author: Vishal Daga
//Date: 10-March-2020

#include <ESP8266WiFi.h>
#define PubNub_BASE_CLIENT WiFiClient
#include <PubNub.h>
#include <ArduinoJson.h>

static char ssid[] = "Tenda_435C38";
static char pass[] = "visdnick";
//static char ssid[] = "Visd";
//static char pass[] = "visdnick";
const static char pubkey[]  = "pub-c-150da624-63d5-4b29-812c-dde769508367";
const static char subkey[]  = "sub-c-2ee8f996-6133-11ea-aaa3-eab2515ceb0d";
const static char PUBNUB_IN_CHANNEL[] = "visdInverterOperator01In";
const static char PUBNUB_OUT_CHANNEL[] = "visdInverterOperator01Out";


//int relay1Pin = 4; // D2 Pin on NODEMCU
//int relay0Pin = 5; // D1 Pin on NODEMCU

int relay1Pin = 2; // D2 Pin on NODEMCU
int relay0Pin = 0; // D1 Pin on NODEMCU

byte instruction[100];

void publishToChannel(const char msg[]){
  Serial.println("publishing...");
  WiFiClient* client = PubNub.publish(PUBNUB_IN_CHANNEL, msg);
  if (0 == client) {
      Serial.println("Error publishing message.");
      delay(1000);
      return;
  }
  client->stop();
}

StaticJsonDocument<200> pubnubMessage;

void setup(){
  Serial.begin(9600);
  Serial.println("Attempting to connect...");
  
  WiFi.begin(ssid, pass); //ESP8266WiFi SDK provides the WiFi object which does the connection to WiFi

  if(WiFi.waitForConnectResult() != WL_CONNECTED) { // Connect to WiFi.
    Serial.println("Couldn't connect to WiFi.");
    while(1) delay(100);
  } else {
    Serial.println("Connected to WIFI");

    //After connection to wifi, with PUBNUB sdk using PubNub object, intilizing the PubNub with the publish and subscribe key
    PubNub.begin(pubkey, subkey);
    Serial.println("PubNub is set up.");
  }

  pinMode(relay1Pin, OUTPUT);
  pinMode(relay0Pin, OUTPUT);
  digitalWrite(relay1Pin, LOW);
  digitalWrite(relay0Pin, HIGH);
}

void loop(){
    {
      //subscribing
      PubSubClient* sclient = PubNub.subscribe(PUBNUB_IN_CHANNEL);
      if (0 == sclient) { 
        Serial.println("Error subscribing to channel.");
        delay(1000);
        return;
      }
      //successfully subscribed
  
      //waiting in an infinite loop for message
      int i = 0;
      while (sclient->wait_for_data()) {
        int insLen = sclient->read();
        instruction[i] = insLen;
        i++;
      }
      char inst[i-1];
      for(int j = 0; j < i; j++){
        inst[j] = instruction[j];
      }
  
      DeserializationError error = deserializeJson(pubnubMessage, inst);
  
      if (error) {
        Serial.print(F("deserializeJson() failed: "));
        Serial.println(error.c_str());
      }
  
      String ins = pubnubMessage[0]["ins"];
      String insSerial = pubnubMessage[0]["serial"];
      
      if (ins == "00"){
        digitalWrite(relay1Pin, LOW);
        digitalWrite(relay0Pin, LOW);
        Serial.println("insF");
        publishToChannel(insSerial.c_str());
  
      } else if (ins == "01"){
        digitalWrite(relay1Pin, LOW);
        digitalWrite(relay0Pin, HIGH);
        Serial.println("insS");
        publishToChannel(insSerial.c_str());
      } else if (ins == "10"){
        digitalWrite(relay1Pin, HIGH);
        digitalWrite(relay0Pin, LOW);
        Serial.println("insT");
        publishToChannel(insSerial.c_str());
      } else if (ins == "11"){
        digitalWrite(relay1Pin, HIGH);
        digitalWrite(relay0Pin, HIGH);
        Serial.println("insFo");
        publishToChannel(insSerial.c_str());
      }
      sclient->stop();
    }
}
