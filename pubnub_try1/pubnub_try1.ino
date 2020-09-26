// PubNub example using ESP8266.
#include <ESP8266WiFi.h>
#define PubNub_BASE_CLIENT WiFiClient
#include <PubNub.h>
static char ssid[] = "Tenda_435C38";
static char pass[] = "visdnick";
const static char pubkey[]  = "pub-c-150da624-63d5-4b29-812c-dde769508367";
const static char subkey[]  = "sub-c-2ee8f996-6133-11ea-aaa3-eab2515ceb0d";
const static char channel[] = "hello_world";
String message;
void setup() {
    Serial.begin(9600);
    Serial.println("Attempting to connect...");
    WiFi.begin(ssid, pass);
    if(WiFi.waitForConnectResult() != WL_CONNECTED) { // Connect to WiFi.
        Serial.println("Couldn't connect to WiFi.");
        while(1) delay(100);
    }
    else {
        Serial.print("Connected to SSID: ");
        Serial.println(ssid);
        PubNub.begin(pubkey, subkey); // Start PubNub.
        Serial.println("PubNub is set up.");
    }
}
void loop() {
    { // Subscribe.
        PubSubClient* sclient = PubNub.subscribe(channel); // Subscribe.
        if (0 == sclient) { 
            Serial.println("Error subscribing to channel.");
            delay(1000);
            return;
        }
        while (sclient->wait_for_data()) { // Print messages.
            Serial.write(sclient->read());
        }
        sclient->stop();
    }
    { // Publish.
        char msg[] = "\"Hello world\"";
        WiFiClient* client = PubNub.publish(channel, msg); // Publish message.
        if (0 == client) {
            Serial.println("Error publishing message.");
            delay(1000);
            return;
        }
        client->stop();
    }
    delay(1000);
}
