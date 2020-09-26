// PubNub MQTT example using ESP8266.
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
// Connection info.
const char* ssid = "Tenda_435C38";
const char* password =  "visdnick";
const char* mqttServer = "mqtt.pndsn.com";
const int mqttPort = 1883;
const char* clientID =  "pub-c-150da624-63d5-4b29-812c-dde769508367";
const char* channelName = "hello_world";
WiFiClient MQTTclient;
PubSubClient client(MQTTclient);
void callback(char* topic, byte* payload, unsigned int length) {
  String payload_buff;
  for (int i=0;i<length;i++) {
    payload_buff = payload_buff+String((char)payload[i]);
  }
  Serial.println(payload_buff); // Print out messages.
}
long lastReconnectAttempt = 0;
boolean reconnect() {
  if (client.connect(clientID)) {
    client.subscribe(channelName); // Subscribe.
  }
  return client.connected();
}
void setup() {
  Serial.begin(9600);
  Serial.println("Attempting to connect...");
  WiFi.begin(ssid, password); // Connect to WiFi.
  if(WiFi.waitForConnectResult() != WL_CONNECTED) {
      Serial.println("Couldn't connect to WiFi.");
      while(1) delay(100);
  }
  client.setServer(mqttServer, mqttPort); // Connect to PubNub.
  client.setCallback(callback);
  lastReconnectAttempt = 0;
}
void loop() {
  Serial.println("00");
  if (!client.connected()) {
    Serial.println("01");
    long now = millis();
    if (now - lastReconnectAttempt > 5000) { // Try to reconnect.
      lastReconnectAttempt = now;
      if (reconnect()) { // Attempt to reconnect.
        lastReconnectAttempt = 0;
      }
    }
  } else { // Connected.
    Serial.println("02");
    client.loop();
    client.publish(channelName,"Hello world!"); // Publish message.
    delay(1000);
  }
}
