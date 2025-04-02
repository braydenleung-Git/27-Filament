#include <Stepper.h>

const int stepsPerRevolution = 2048;
Stepper myStepper(stepsPerRevolution, 8, 10, 9, 11);

const int buttonPin = 2;

int stepCount = 0;
bool wasPressed = false;

void setup() {
  pinMode(buttonPin, INPUT_PULLUP);  // Button connected to GND when pressed
  myStepper.setSpeed(10);
  Serial.begin(9600);  // Start serial communication
}

void loop() {
  bool isPressed = (digitalRead(buttonPin) == LOW);

  if (isPressed) {
    myStepper.step(1);
    stepCount++;x
    wasPressed = true;
  } else {
    if (wasPressed) {
      // Button was just released — report step count
      Serial.print("Steps taken during button press: ");
      Serial.println(stepCount);
      stepCount = 0;
      wasPressed = false;
    }
  }
}
