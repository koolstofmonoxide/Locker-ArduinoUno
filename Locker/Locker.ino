#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

// Set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Assigning Button Pins
const int Button_1 = 5;
const int Button_2 = 4;
const int Button_3 = 3;
const int Button_Enter = 2;

const int ledPin = 11;

bool setupMode = true;

// Defined correct Code for locker
int universalCode[] = {1, 2, 3};
int correctCode[3];

int userInput[3];
int inputPosition = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(ledPin, OUTPUT);

  pinMode(Button_1, INPUT);
  pinMode(Button_2, INPUT);
  pinMode(Button_3, INPUT);
  pinMode(Button_Enter, INPUT);

  Serial.begin(9600);

  lcd.begin();  

  lcd.print("Setup Mode");
  lcd.setCursor(0, 1);
  lcd.print("Enter new code");

}

void loop() {
  // put your main code here, to run repeatedly:
  if (setupMode) {
    checkButton(Button_1, 1);
    checkButton(Button_2, 2);
    checkButton(Button_3, 3);

    if (digitalRead(Button_Enter) == HIGH) {
      delay(200);
      lcd.clear();

      // Copy user input to correctCode
      for (int i = 0; i < 3; i++) {
        correctCode[i] = userInput[i];
      }

      lcd.print("Setup Complete");

      // Reset userInput array and position
      memset(userInput, 0, 3 * sizeof(int));
      inputPosition = 0;

      setupMode = false;

      delay(1000);
    }
  }
  else{
    checkButton(Button_1, 1);
    checkButton(Button_2, 2);
    checkButton(Button_3, 3);

    if (digitalRead(Button_Enter) == HIGH) {
      delay(200);
      CheckCode();
    }
  }
}

void checkButton(int buttonPin, int buttonNumber) {
  if (digitalRead(buttonPin) == HIGH) {
    digitalWrite(ledPin, HIGH); // Light up LED on button Press

    userInput[inputPosition] = buttonNumber; // Add chosen number to array

    inputPosition = inputPosition + 1; // Move to next position in the array

    while (digitalRead(buttonPin) == HIGH) {
      delay(100);
    }

    digitalWrite(ledPin, LOW); // Turn led off
  }
}

void CheckCode() {
  lcd.rightToLeft();
  bool codeCorrect = true;

  for (int i = 0; i < 3; i++) {
    if (userInput[i] != correctCode[i]) {
      codeCorrect = false;
      break;
    }
  }

  if (codeCorrect) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Code is correct,");
    lcd.setCursor(0, 1);
    lcd.print("locker opened!");
  }
  else {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Incorrect code,");
    lcd.setCursor(0, 1);
    lcd.print("try again.");
  }

  // Reset userInput array and position
  memset(userInput, 0, 3 * sizeof(int));
  inputPosition = 0;
}