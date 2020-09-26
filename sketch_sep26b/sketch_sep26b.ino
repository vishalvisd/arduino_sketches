int control1 = 0;
int control2 = 0;
int control3 = 0;
int control4 = 0;

#define panel_1_control_signal_pin  2
#define panel_2_control_signal_pin  3
#define panel_3_control_signal_pin  4
#define panel_4_control_signal_pin  5

void setup() {
//-------( Initialize Pins so relays are inactive at reset)----
  Serial.begin(9600);
  digitalWrite(panel_1_control_signal_pin, HIGH);
  digitalWrite(panel_2_control_signal_pin, HIGH);
  digitalWrite(panel_3_control_signal_pin, HIGH);
  digitalWrite(panel_4_control_signal_pin, HIGH);  
  
//---( THEN set pins as outputs )----  
  pinMode(panel_1_control_signal_pin, OUTPUT);   
  pinMode(panel_2_control_signal_pin, OUTPUT);  
  pinMode(panel_3_control_signal_pin, OUTPUT);  
  pinMode(panel_4_control_signal_pin, OUTPUT);    
  delay(4000); //Check that all relays are inactive at Reset
}

void loop() {
  //read voltage
  int panel1VoltageSensorReading = analogRead(A0);
  float panelVoltage = map(panel1VoltageSensorReading, 0, 1023, 0, 2500);
  panelVoltage /= 100;
  if (panelVoltage < 7){
    control1 = HIGH;
    control2 = HIGH;
    control3 = HIGH;
    control4 = HIGH;
  } else if (panelVoltage < 13){
    control1 = LOW;
    control2 = HIGH;
    control3 = LOW;
    control4 = HIGH;
  } else {
    control1 = LOW;
    control2 = LOW;
    control3 = LOW;
    control4 = LOW;
  }
  digitalWrite(panel_1_control_signal_pin, control1);
  digitalWrite(panel_2_control_signal_pin, control2);
  digitalWrite(panel_3_control_signal_pin, control3);
  digitalWrite(panel_4_control_signal_pin, control4);
  Serial.println(panelVoltage);
}
