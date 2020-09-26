/*********
  Rui Santos
  Complete project details at http://randomnerdtutorials.com  
*********/

// Load Wi-Fi library
#include <ESP8266WiFi.h>

// Replace with your network credentials
const char* ssid     = "Tenda_435C38";
const char* password = "visdnick";

// Set web server port number to 80
WiFiServer server(80);

// Variable to store the HTTP request
String header;

// Auxiliar variables to store the current output state
int outState = 0;
int onMin = 0;

// Current time
unsigned long currentTime = millis();
// Previous time
unsigned long previousTime = 0; 
// Define timeout time in milliseconds (example: 2000ms = 2s)
const long timeoutTime = 2000;

void setup() {
  Serial.begin(9600);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    serial.write(".");
  }
  // Print local IP address and start web server
  serial.write("");
  serial.write("WiFi connected.");
  serial.write("IP address: ");
  serial.write(WiFi.localIP());
  
  server.begin();
}

void loop(){
  WiFiClient client = server.available();   // Listen for incoming clients
  if (client) {                             // If a new client connects,
    String currentLine = "";                // make a String to hold incoming data from the client
    currentTime = millis();
    previousTime = currentTime;
    while (client.connected() && currentTime - previousTime <= timeoutTime) { // loop while the client's connected
      currentTime = millis();         
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        header += c;
        if (c == '\n') {                    // if the byte is a newline character
          if (currentLine.length() == 0) {
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();
            
            if (header.indexOf("GET /turnoff") >= 0) {
              serial.write("0000");
              outState = 0;
              onMin=0;
            } else if (header.indexOf("GET /turnon/1min") >= 0) {
              serial.write("1001");
              outState = 1;
              onMin=1;
            } else if (header.indexOf("GET /turnon/5min") >= 0) {
              serial.write("1005");
              outState = 1;
              onMin=5;
            } else if (header.indexOf("GET /turnon/10min") >= 0) {
              serial.write("1010");
              outState = 1;
              onMin=10;
            } else if (header.indexOf("GET /turnon/20min") >= 0) {
              serial.write("1020");
              outState = 1;
              onMin=20;
            } else if (header.indexOf("GET /turnon/30min") >= 0) {
              serial.write("1030");
              outState = 1;
              onMin=30;
            } else if (header.indexOf("GET /turnon/60min") >= 0) {
              serial.write("1060");
              outState = 1;
              onMin=60;
            } else if (header.indexOf("GET /turnon/180min") >= 0) {
              serial.write("1180");
              outState = 1;
              onMin=180;
            } else {
              serial.write("0000");
              outState = 0;
              onMin=0;
            }
            
            // Display the HTML web page
            client.println("<!DOCTYPE html><html>");
            client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
            client.println("<link rel=\"icon\" href=\"data:,\">");
            // CSS to style the on/off buttons 
            // Feel free to change the background-color and font-size attributes to fit your preferences
            client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
            client.println(".button { background-color: #195B6A; border: none; color: white; padding: 16px 40px;");
            client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
            client.println(".button2 {background-color: #77878A;}</style></head>");
            
            // Web Page Heading
            client.println("<body><h1>VISD system: Force Grid Supply Into Inverter</h1>");

            if (outState == 1){
              client.print("<p>Current State: On for ");
              client.print(onMin);
              client.println(" mins</p>");
              client.println("<p><a href=\"/turnoff\"><button class=\"button\">OFF</button></a></p>");
            } else if (outState == 0){
              client.println("<p>Current State: Off </p>");
              
              client.println("<p><button class=\"button button2\">OFF</button></p>");
              
              client.println("<p><a href=\"/turnon/1min\"><button class=\"button\">ON for 1 min</button></a></p>");
              client.println("<p><a href=\"/turnon/5min\"><button class=\"button\">ON for 5 mins</button></a></p>");
              client.println("<p><a href=\"/turnon/10min\"><button class=\"button\">ON for 10 mins</button></a></p>");
              client.println("<p><a href=\"/turnon/20min\"><button class=\"button\">ON for 20 mins</button></a></p>");
              client.println("<p><a href=\"/turnon/30min\"><button class=\"button\">ON for 30 mins</button></a></p>");
              client.println("<p><a href=\"/turnon/60min\"><button class=\"button\">ON for 60 mins</button></a></p>");
              client.println("<p><a href=\"/turnon/180min\"><button class=\"button\">ON for 180 mins</button></a></p>");
            }
               
            client.println("</body></html>");
            
            // The HTTP response ends with another blank line
            client.println();
            // Break out of the while loop
            break;
          } else { // if you got a newline, then clear currentLine
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }
      }
    }
    // Clear the header variable
    header = "";
    // Close the connection
    client.stop();
  }
}
