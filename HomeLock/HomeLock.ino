// Include the Keypad library
#include <Keypad.h>

// Constants for row and column sizes
const byte ROWS = 4;
const byte COLS = 4;

// Array to represent keys on keypad
char hexaKeys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

// Connections to Arduino
byte rowPins[ROWS] = {9, 8, 7, 6};
byte colPins[COLS] = {5, 4, 3, 2};

// Create keypad object
Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);
 

short seedRandom;
short lockcounter;
short lockskip;
boolean waitingtogetunlockkey = false;
String userinput;

void setConditionalRandomSeed(){
  if(lockcounter > 30){
    // 0x
    Serial.println("Setting random seed again...");
    randomSeed(analogRead(0));
    seedRandom = random(10, 99);
    Serial.print("Setting new random seed as: ");
    Serial.println(seedRandom);
    randomSeed(seedRandom);
    lockskip = 1;
    lockcounter = 10;
  }
  
}

void setup() {
  Serial.begin(9600);
  
  randomSeed(analogRead(0));
  seedRandom = random(1, 900);
  
  // 0x 
  Serial.print("Taking random seed as:");
  Serial.println(seedRandom);
  randomSeed(seedRandom);

  // initialize the lock counter
  lockskip = 1;
  lockcounter = 10;
}

void loop() {
  if (waitingtogetunlockkey == false){
    setConditionalRandomSeed();
    // genrating the public lock code
    short publiclock = random(1000, 9999);
  
    // suffix the lock counter and the random seed to the public lock code
    String displayCodeString = String(publiclock) + String(lockcounter) + String(seedRandom);
    
    // Display this number to LCD
    Serial.println(displayCodeString);

    waitingtogetunlockkey = true;
    Serial.println("Waiting for user to unlock...");
    
    //increment the lock counter
    lockcounter = lockcounter + lockskip;
    lockskip++;
  } else {
    // 0x
//    Serial.println("Waiting for user input");
    // Get key value if pressed
    char customKey = customKeypad.getKey();
    if(customKey){
      userinput = userinput + customKey;
      Serial.print(customKey);
      if (userinput.length() == 4) {
        Serial.println("");
        short unlockpin = random(1000, 9999);
  
        lockcounter = lockcounter + lockskip;
        lockskip++;
  
        if (String(unlockpin).equals(userinput)){
          // 0x
          Serial.println("Unlocked");
          // unlock the door
        } else {
          Serial.println("Pin didn't match");
        }
        userinput = "";
        waitingtogetunlockkey = false;
      }
    }
    
  }
}
