int numberOfBatteries = 3;

int connectorRelay1 = 7;
int connectorRelay2 = 3;

int switchingRelay1 = 12;
int switchingRelay2 = 10;

long oneHour = 30000;

int nextSetupIndex = 0;

void useBattery1And2(){
  digitalWrite(connectorRelay1, LOW);
  digitalWrite(switchingRelay1, LOW);
}

void useBattery2And3(){
  digitalWrite(connectorRelay1, LOW);
  digitalWrite(switchingRelay1, LOW);
}

void useBattery1And3(){
  digitalWrite(connectorRelay1, LOW);
  digitalWrite(switchingRelay1, LOW);
}

void selectAndSetBatterySetup(){
    if (nextSetupIndex == 0){
        useBattery1And2();
    } else if (nextSetupIndex == 1) {
        useBattery2And3();
    } else if (nextSetupIndex == 2) {
        useBattery1And3();
    }
    nextSetupIndex++;
    if (nextSetupIndex >= numberOfBatteries){
      nextSetupIndex = 0;
    }
    delay(oneHour);
}
void setup() {
  pinMode(connectorRelay1, OUTPUT);
  pinMode(switchingRelay1, OUTPUT);
  
 

   
  selectAndSetBatterySetup();
}

void loop(){
  selectAndSetBatterySetup();
  
}
