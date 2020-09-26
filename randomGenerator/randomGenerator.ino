boolean printed = false;
void setup() {
  Serial.begin(9600);
}

void loop() {
  if(printed == false){
    Serial.print("[");
    for(int i = 1000; i < 1250; i++){
      randomSeed(i);
      for(int j = 0; j < 6; j++){
        short randomValue = random(1000, 9999);
        Serial.print(randomValue);
        Serial.print(",");
      }
    }
    Serial.print("]");
    printed = true;
  }
}
