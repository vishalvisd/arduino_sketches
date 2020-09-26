int led1Pin = 4;
int led2Pin = 5; 

void setup() {
  Serial.begin(9600);
  pinMode(led1Pin, OUTPUT);
  pinMode(led2Pin, OUTPUT);
  
  digitalWrite(led1Pin, LOW);
  digitalWrite(led2Pin, LOW);
  Serial.println(" high");

}

void loop() {

  digitalWrite(led1Pin, HIGH);
  Serial.println("led1Pin high");
  delay(1000);
  digitalWrite(led1Pin, LOW);

  digitalWrite(led2Pin, HIGH);
  Serial.println("led2Pin high");
  delay(1000);
  digitalWrite(led2Pin, LOW);


}
