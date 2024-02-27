// Assigning Button Pins
const int Button_1 = 5;
const int Button_2 = 4;
const int Button_3 = 3;
const int Button_Enter = 2;

const int ledPin = 11;

// Defined correct Code for locker
int correctCode[] = {1, 2, 3};

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
}

void loop() {
  // put your main code here, to run repeatedly:
  checkButton(Button_1, 1);
  checkButton(Button_2, 2);
  checkButton(Button_3, 3);

  if (digitalRead(Button_Enter) == HIGH) {
    CheckCode();
  }
}

void checkButton(int buttonPin, int buttonNumber) {
  if (digitalRead(buttonPin) == HIGH) {
    digitalWrite(ledPin, HIGH); // Light up LED on button Press

    userInput[inputPosition] = buttonNumber; // Add chosen number to array

    inputPosition = (inputPosition + 1) % 3; // Move to next position in the array

    while (digitalRead(buttonPin) == HIGH) {
      delay(100);
    }

    digitalWrite(ledPin, LOW); // Turn led off
  }
}

void CheckCode() {
  bool codeCorrect = true;

  for (int i = 0; i < 3; i++) {
    if (userInput[i] != correctCode[i]) {
      codeCorrect = false;
      break;
    }
  }

  if (codeCorrect) {
    Serial.println("Code is correct, locker opened!");
  }
  else {
    Serial.println("Code is incorrect, please try again.");
  }

  // Reset userInput array and position
  memset(userInput, 0, 3 * sizeof(int));
  inputPosition = 0;
}