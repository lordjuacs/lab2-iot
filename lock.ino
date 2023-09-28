#include <Servo.h>
#include <Keypad.h>

const byte ROWS = 4; 
const byte COLS = 4; 
char keys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};
byte rowPins[ROWS] = {2, 3, 4, 5}; 
byte colPins[COLS] = {6, 7, 8, 9};

Servo servo;
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);
String password = "9090";

void setup() {
  servo.attach(10);
  servo.write(0);
  delay(1000);
  Serial.begin(9600);
}


void loop() {
  String input = ""; // Initialize input as an empty string
  int count = 1;
  while (count < 5) {
    char key = keypad.getKey();
    if (key) {
      input += key;
      count++;
      Serial.println(key);
    }
  }
  Serial.println(input);
  Serial.println(password);
  if (input == password) {
    servo.write(90);
    delay(5000);
    servo.write(0); // Lock the servo after a successful unlock
    input = ""; // Clear the input
    count = 1;
  } else {
    Serial.println("\nIncorrect password!");
    input = ""; // Clear the input for the next attempt
    count = 1;
  }
}
