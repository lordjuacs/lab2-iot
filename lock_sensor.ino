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

const int triggerPin = 12; // HC-SR04 trigger pin
const int echoPin = 11;    // HC-SR04 echo pin
const float maxDistance = 100; // Maximum distance in centimeters (1 meter)

bool lockOpen = false;

void setup() {
  servo.attach(10);
  servo.write(0);
  delay(1000);
  Serial.begin(9600);
  pinMode(triggerPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop() {
  String input = ""; // Initialize input as an empty string
  int count = 1;
  
  // Ask for input password
    Serial.println("Enter password:");

  while (count < 5) {
    char key = keypad.getKey();
    if (key) {
      input += key;
      count++;
      Serial.print(key);
    }
  }
  
  Serial.println(input);

  if (input == password) {
    input = ""; // Clear the input
    count = 1;
    Serial.println("Correct!\n");
    lockOpen = true;
    servo.write(90);
    // Check proximity and keep the lock open if someone is close
    while (lockOpen) {
      // Check the distance using the HC-SR04 sensor
      //digitalWrite(triggerPin, LOW);
      //delayMicroseconds(2);
      digitalWrite(triggerPin, HIGH);
      delayMicroseconds(10);
      digitalWrite(triggerPin, LOW);

      long duration = pulseIn(echoPin, HIGH);
      float distance_cm = duration / 59.0;

      //Serial.println(distance_cm);

      if (distance_cm > maxDistance) {
        // Lock the servo if someone is not close
        servo.write(0);
        lockOpen = false;
        Serial.println("Locking...");
      }
    }
  } else {
    Serial.println("Incorrect password!\n");
    input = ""; // Clear the input for the next attempt
    count = 1;
  }
}
