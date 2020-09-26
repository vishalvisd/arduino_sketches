void setup() {
  Serial.begin(9600);
  pinMode(2, OUTPUT);
}

void loop() {
  String isBoradRelayOn = Serial.readString();
  Serial.write("got:");
  if (isBoradRelayOn.indexOf("r1c") >= 0){
     digitalWrite(2, LOW);
  } else if (isBoradRelayOn.indexOf("r0c") >= 0){
    digitalWrite(2, HIGH);
  }
  Serial.flush();
}
