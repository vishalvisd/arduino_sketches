const int voltageSensor = A0;

float vOUT = 0.0;
float vIN = 0.0;
int value = 0;
const float batMinThres = 21.7; //22.5 volt
const int gridElectricRelayPin = 3;
const int segmentA = 4;
const int segmentB = 5;
const int segmentC = 6;
const int segmentD = 7;
const int segmentE = 8;
const int segmentF = 9;
const int segmentG = 2;

int counter = 0;

unsigned long millisStart = 0;
unsigned long millisFor = 0;

void setup()
{
  pinMode(gridElectricRelayPin, OUTPUT); 

  pinMode(segmentA, OUTPUT);
  pinMode(segmentB, OUTPUT);
  pinMode(segmentC, OUTPUT);
  pinMode(segmentD, OUTPUT);
  pinMode(segmentE, OUTPUT);
  pinMode(segmentF, OUTPUT);
  pinMode(segmentG, OUTPUT);
  
  digitalWrite(gridElectricRelayPin, HIGH);

  digitalWrite(segmentA, LOW);
  digitalWrite(segmentB, LOW);
  digitalWrite(segmentC, LOW);
  digitalWrite(segmentD, LOW);
  digitalWrite(segmentE, LOW);
  digitalWrite(segmentF, LOW);
  digitalWrite(segmentG, LOW);
  
  Serial.begin(9600); 
}

void printNumber(int n){
  if(n == 0){
    print0();
  } else if(n == 1){
    print1();
  } else if(n == 2){
    print2();
  } else if(n == 3){
    print3();
  } else if(n == 4){
    print4();
  } else if(n == 5){
    print5();
  } else if(n == 6){
    print6();
  } else if(n == 7){
    print7();
  } else if(n == 8){
    print8();
  } else if(n == 9){
    print9();
  } 
}

void print0(){
  digitalWrite(segmentA, HIGH);
  digitalWrite(segmentB, HIGH);
  digitalWrite(segmentC, HIGH);
  digitalWrite(segmentD, HIGH);
  digitalWrite(segmentE, HIGH);
  digitalWrite(segmentF, HIGH);
  digitalWrite(segmentG, LOW);
}

void print1(){
  digitalWrite(segmentA, LOW);
  digitalWrite(segmentB, HIGH);
  digitalWrite(segmentC, HIGH);
  digitalWrite(segmentD, LOW);
  digitalWrite(segmentE, LOW);
  digitalWrite(segmentF, LOW);
  digitalWrite(segmentG, LOW);
}

void print2(){
  digitalWrite(segmentA, HIGH);
  digitalWrite(segmentB, HIGH);
  digitalWrite(segmentC, LOW);
  digitalWrite(segmentD, HIGH);
  digitalWrite(segmentE, HIGH);
  digitalWrite(segmentF, LOW);
  digitalWrite(segmentG, HIGH);
}

void print3(){
  digitalWrite(segmentA, HIGH);
  digitalWrite(segmentB, HIGH);
  digitalWrite(segmentC, HIGH);
  digitalWrite(segmentD, HIGH);
  digitalWrite(segmentE, LOW);
  digitalWrite(segmentF, LOW);
  digitalWrite(segmentG, HIGH);
}

void print4(){
  digitalWrite(segmentA, LOW);
  digitalWrite(segmentB, HIGH);
  digitalWrite(segmentC, HIGH);
  digitalWrite(segmentD, LOW);
  digitalWrite(segmentE, LOW);
  digitalWrite(segmentF, HIGH);
  digitalWrite(segmentG, HIGH);
}

void print5(){
  digitalWrite(segmentA, HIGH);
  digitalWrite(segmentB, LOW);
  digitalWrite(segmentC, HIGH);
  digitalWrite(segmentD, HIGH);
  digitalWrite(segmentE, LOW);
  digitalWrite(segmentF, HIGH);
  digitalWrite(segmentG, HIGH);
}

void print6(){
  digitalWrite(segmentA, HIGH);
  digitalWrite(segmentB, LOW);
  digitalWrite(segmentC, HIGH);
  digitalWrite(segmentD, HIGH);
  digitalWrite(segmentE, HIGH);
  digitalWrite(segmentF, HIGH);
  digitalWrite(segmentG, HIGH);
}

void print7(){
  digitalWrite(segmentA, HIGH);
  digitalWrite(segmentB, HIGH);
  digitalWrite(segmentC, HIGH);
  digitalWrite(segmentD, LOW);
  digitalWrite(segmentE, LOW);
  digitalWrite(segmentF, LOW);
  digitalWrite(segmentG, LOW);
}

void print8(){
  digitalWrite(segmentA, HIGH);
  digitalWrite(segmentB, HIGH);
  digitalWrite(segmentC, HIGH);
  digitalWrite(segmentD, HIGH);
  digitalWrite(segmentE, HIGH);
  digitalWrite(segmentF, HIGH);
  digitalWrite(segmentG, HIGH);
}

void print9(){
  digitalWrite(segmentA, HIGH);
  digitalWrite(segmentB, HIGH);
  digitalWrite(segmentC, HIGH);
  digitalWrite(segmentD, HIGH);
  digitalWrite(segmentE, LOW);
  digitalWrite(segmentF, HIGH);
  digitalWrite(segmentG, HIGH);
}

void printEmpty(){
  digitalWrite(segmentA, LOW);
  digitalWrite(segmentB, LOW);
  digitalWrite(segmentC, LOW);
  digitalWrite(segmentD, LOW);
  digitalWrite(segmentE, LOW);
  digitalWrite(segmentF, LOW);
  digitalWrite(segmentG, LOW);
}


void printR(){
  digitalWrite(segmentA, HIGH);
  digitalWrite(segmentB, HIGH);
  digitalWrite(segmentC, HIGH);
  digitalWrite(segmentD, LOW);
  digitalWrite(segmentE, HIGH);
  digitalWrite(segmentF, HIGH);
  digitalWrite(segmentG, HIGH);
}

void loop()
{
  printNumber(8);
  delay(1000);
  if (millis() - millisStart > millisFor){
    value = analogRead(voltageSensor);
    Serial.print(value);
    Serial.print(" value: ");
    vOUT = (value * 5.0) / 1024.0;
    Serial.print(vOUT);
    Serial.print(" vOUT: ");
    vIN = vOUT / 0.2;
    Serial.print(vIN);
    Serial.println(" vIN: ");
    

    if (vIN < batMinThres && vIN != 0){
       printNumber(9);
       digitalWrite(gridElectricRelayPin, LOW);
       millisStart = millis();
       millisFor = 600000;
//       millisFor = 5000;
    } else {
      printNumber(7);
      digitalWrite(gridElectricRelayPin, HIGH);
    }
  }
 

  String command = Serial.readString();
  Serial.print(command);
  if (command != ""){
    if(command.indexOf("0000") >= 0){
      digitalWrite(gridElectricRelayPin, HIGH);
      printNumber(0);
      millisStart = millis();
//      millisFor = 30000;
      millisFor = 3000;
    } else if (command.indexOf("1001") >= 0){
       printNumber(1);
       digitalWrite(gridElectricRelayPin, LOW);
       millisStart = millis();
       millisFor = 60000;
    } else if (command.indexOf("1005") >= 0){
       printNumber(2);
       digitalWrite(gridElectricRelayPin, LOW);
       millisStart = millis();
       millisFor = 300000;
     } else if (command.indexOf("1010") >= 0){
       printNumber(3);
       digitalWrite(gridElectricRelayPin, LOW);
       millisStart = millis();
       millisFor = 600000;
     } else if (command.indexOf("1020") >= 0){
       printNumber(4);
       digitalWrite(gridElectricRelayPin, LOW);
       millisStart = millis();
       millisFor = 1200000;
     } else if (command.indexOf("1030") >= 0){
       printNumber(5);
       digitalWrite(gridElectricRelayPin, LOW);
       millisStart = millis();
       millisFor = 1800000;
     } else if (command.indexOf("1060") >= 0){
       printNumber(6);
       millisStart = millis();
       millisFor = 3600000;
     } else if (command.indexOf("1180") >= 0){
       digitalWrite(gridElectricRelayPin, LOW);
       millisStart = millis();
       millisFor = 10800000;
    }
  }
  delay(1000);
  printNumber(0);
  delay(1000);
}
