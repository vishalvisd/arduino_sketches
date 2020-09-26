const int voltageSensor = A0;

float vOUT = 0.0;
float vIN = 0.0;
int value = 0;
const int batMinThres = 23; //23 volt
const int gridElectricRelayPin = 10;
int gridOn = false;

void setup()
{
    Serial.begin(9600);
  pinMode(gridElectricRelayPin, OUTPUT);
  digitalWrite(gridElectricRelayPin, HIGH);
}

void loop()
{
  Serial.println(gridOn);
  if (gridOn == false){
    digitalWrite(gridElectricRelayPin, HIGH);
    Serial.println(" HIGH ");
    gridOn = true;
  } else if (gridOn == true){
    digitalWrite(gridElectricRelayPin, LOW);
     Serial.println("LOW ");
    gridOn = false;
  }
  delay(3000);
}
