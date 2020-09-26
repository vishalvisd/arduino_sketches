/*
Measuring AC Current Using ACS712
www.circuits4you.com
*/
const int sensorIn = A0;
int mVperAmp = 185; // use 100 for 20A Module and 66 for 30A Module

double Voltage = 0;
double VRMS = 0;
double AmpsRMS = 0;
//int timenowmill = 10.6  * 60;
//int nightStart = 16 * 60;
//int dayStart = 8.5 * 60;
//int minCounter = 0;

//
const float sleepCurrentT = 0.1;
const float cOnCurrentT = 1;

const int relayPin = 3;
const int bulbRelayPin = 8;

int currentState = NULL;
//int daystate = NULL; //0 is day, 1 is night
//bool ledBuState = false;
//

float getVPP()
{
  float result;
  int readValue;             //value read from the sensor
  int maxValue = 0;          // store max value here
  int minValue = 1024;          // store min value here
  
   uint32_t start_time = millis();
   while((millis()-start_time) < 980) //sample for 1 Sec [keeping 980 instead 1000 for acconting drift]
   {
       readValue = analogRead(sensorIn);
       // see if you have a new maxValue
       if (readValue > maxValue) 
       {
           /*record the maximum sensor value*/
           maxValue = readValue;
       }
       if (readValue < minValue) 
       {
           /*record the minimum sensor value*/
           minValue = readValue;
       }
   }
   
   // Subtract min from max
   result = ((maxValue - minValue) * 5.0)/1024.0;
   
//   minCounter = minCounter + 1;
//   if (minCounter == 60){
//    minCounter = 0;
//    timenowmill = timenowmill + 1;
//   }
//   
//   if (timenowmill == 1440){
//    timenowmill = 0;
//   }
//   if (timenowmill > dayStart && timenowmill < nightStart){
//     daystate = 0;
//   } else {
//     daystate = 1;
//   }
//   if (daystate == 0){
//      if (ledBuState == false){
//        ledBuState = true;
//        digitalWrite(LED_BUILTIN, LOW);
//      } else {
//        ledBuState = false;
//        digitalWrite(LED_BUILTIN, HIGH);
//      }     
//   }
   return result;
 }

int getState(double amps){
  if (amps <= sleepCurrentT){
    return 0;
  }
  if (amps <= cOnCurrentT){
    return 1;
  }
  if (amps > cOnCurrentT){
    return 2;
  }
}

void handleNextState(double amps){  
  int nextState = getState(amps);
  
  if (currentState == 2 && nextState == 1){
    digitalWrite(bulbRelayPin, LOW);
    delay(5000);
    digitalWrite(bulbRelayPin, HIGH);
    digitalWrite(relayPin, LOW); //switchOnRelay;
    delay(3000);
  } else if (nextState != currentState && currentState != NULL) {
    digitalWrite(relayPin, HIGH); //switchOffRelay;
    digitalWrite(bulbRelayPin, HIGH);
  }
  
  currentState = nextState;
}

void setup(){ 
  pinMode(relayPin, OUTPUT);
  pinMode(bulbRelayPin, OUTPUT);
  digitalWrite(relayPin, HIGH);
  digitalWrite(bulbRelayPin, HIGH);
  
//  pinMode(LED_BUILTIN, OUTPUT);
}

void loop(){

 Voltage = getVPP();
 VRMS = (Voltage/2.0) *0.707;  //root 2 is 0.707
 AmpsRMS = (VRMS * 1000)/mVperAmp;
 handleNextState(AmpsRMS);
 
}
