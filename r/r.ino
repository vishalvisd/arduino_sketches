int numberOfBatteries = 3;

int connectorRelay1 = 7;
int connectorRelay2 = 3;

int switchingRelay1 = 12;
int switchingRelay2 = 10;

long oneHour = 3000;

int nextSetupIndex = 0;

void useBattery1And2(){
  digitalWrite(connectorRelay1, HIGH);
  digitalWrite(connectorRelay2, LOW);
  digitalWrite(switchingRelay1, HIGH);
  digitalWrite(switchingRelay2, LOW);
}

void useBattery2And3(){
  digitalWrite(connectorRelay1, LOW);
  digitalWrite(connectorRelay2, HIGH);
  digitalWrite(switchingRelay1, LOW);
  digitalWrite(switchingRelay2, HIGH);
}

void useBattery1And3(){
  digitalWrite(connectorRelay1, HIGH);
  digitalWrite(connectorRelay2, HIGH);
  digitalWrite(switchingRelay1, HIGH);
  digitalWrite(switchingRelay2, HIGH);
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
  pinMode(connectorRelay2, OUTPUT);
  pinMode(switchingRelay1, OUTPUT);
  pinMode(switchingRelay2, OUTPUT);
  
 

   
  selectAndSetBatterySetup();
}

void loop(){
  selectAndSetBatterySetup();
  
}
