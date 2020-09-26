// Author: Vishal Daga
// Date: 19th July, 2020
//
// Features that make it less hackable
// - A new table is selected each iteration
// - Table index is also random selected with no relation to the random seed that let us to 
// select the table
// - The table index is shifted according the its index
// - The final passcode will be next random number is the selected table from the randomly
// selected index

// Include the Keypad library
#include <Keypad.h>

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 2, 1,0, 4, 5, 6, 7, 3, POSITIVE);


// RELAY PIN
short relayPin = 10;

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
byte rowPins[ROWS] = {8, 7, 6, 5};
byte colPins[COLS] = {4, 3, 2, 9};


// Create keypad object
Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);

short randomTable;
short tableIndex;
boolean waitingToUnlock = false;
// Variable to accumulate user input keypad presses till we get 4 digit input
String userInput;
short wrongCounter = 0;
String adminInput = "8281";
boolean adminEnabled = false;

String getPublicCode(){
  // seed from analogRead so that every time the system reboots the sequece of table selection
  // is unpredictable
  randomSeed(analogRead(0));
  randomTable = random(100, 900);

  // We also select the table index between 0 - 4 [5 total]. Also taking new seeder from
  // analog 1 just to make table selection and index selection to be unpredictable between both
  randomSeed(analogRead(1));
  tableIndex = random(0, 5);
  
  // Once the table and table index is selected, we set the random to seed from the table
  // so that the passcode would be the next among the selection
  randomSeed(randomTable);

  short displayTableIndex = 10;
  for(int i = 1; i < tableIndex+1; i++){
    displayTableIndex = displayTableIndex + i + 15;
  }

  return String(displayTableIndex) + String(randomTable);
  
}

void printToLCD(String toDisplay){
    lcd.clear();
    lcd.print(toDisplay);
}

void setup() {
  pinMode(relayPin, OUTPUT);
  digitalWrite(relayPin, HIGH);
  Serial.begin(9600);
  lcd.begin(16, 2);
  lcd.clear();

  //Banner
  lcd.setCursor(0, 0);
  lcd.print("Smart Secure");
  delay(500);
  lcd.setCursor(0, 1);
  printToLCD("Locking System");
  delay(1500);
}

void loop() {
  if(waitingToUnlock == false){
    // Generate the public code
    String publicCode = getPublicCode();
    // Display to LCD the code
    lcd.setCursor(0, 0);
    lcd.clear();
    lcd.print("User PIN: "+publicCode);
    lcd.setCursor(0, 1);
    lcd.print("Unlock PIN:");
    lcd.setCursor(12, 1);
    // 0x
    Serial.println(publicCode);

    // After displaying the public code, go in waiting to unlock mode
    waitingToUnlock = true;
    
    // 0x
    Serial.println("Waiting for User to unlock");
  } else {
    // Public code has been displayed or user has started inputing code using keypad but
    // not yet entered required 4 digit code

    // get the key the user has pressed on keypad
    char customKey = customKeypad.getKey();
    
    if(customKey != NO_KEY){
      // 0x
      Serial.print(customKey);
      // append the user key pad presses and if the size reaches to 4 digit pass to validation
      userInput = userInput + customKey;
      // Display the user input on the LCD screen in the same line till user enter four digits
      lcd.print(customKey);
      // validation of user input after they presses 4 digits
      if(userInput.length() == 4){
        // 0x
        Serial.println("");

        if (String(userInput).equals("****")){
          if (adminEnabled == true){
            adminEnabled = false;
            printToLCD("ADMIN DISABLED!");
          } else {
            adminEnabled = true;
            printToLCD("ADMIN ENABLED!");
          }
          
          delay(1000);
        } else {
          // get the unlock pin - the table has already been seeded here, we have to loop through
          // table index times + 1 which will be our unlock code
          short unlockCode;
          for(int i = 0; i < tableIndex+2; i++){
            unlockCode = random(1000, 9999);
          }
  
          // verify if the user input matches the unlock code
          if(String(unlockCode).equals(userInput) || (adminEnabled == true && String(userInput).equals(adminInput))){
            printToLCD("UNLOCKING...");
  
            // 0x 
            Serial.println("UNLOCKING...");
  
            // set the wrongCounter to 0
            wrongCounter = 0;
            
            // Unlock the lock by sending high signal to relay for eactly 500 milliseconds
            digitalWrite(relayPin, LOW);
            delay(500);
            digitalWrite(relayPin, HIGH);
  
            printToLCD("UNLOCKED!");
  
            // 0x
            Serial.println("UNLOCKED!");
            delay(1000);
          } else {
            printToLCD("Wrong PIN!");
            // 0x
            Serial.println("PIN Didn't matched");
  
            // increment the wrong counter
            wrongCounter = wrongCounter + 1;
            
            // Display to LCD that Wrong PIN
  
            // Wait to show the message
            if(wrongCounter > 8){
              wrongCounter = 8;
            }
  
            delay(1000 + pow(5, wrongCounter));
          }
        }

        // As user has entered 4 digits, we will empty the user input variable
        userInput = "";
        // As user has entered 4 digits, we will again loop back showing the new code to 
        // be decoded to unlock
        waitingToUnlock = false;
      }
      
    }
  }

}
