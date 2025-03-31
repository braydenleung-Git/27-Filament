#include <Wire.h>
#include <Stepper.h>

const int stepsPerRevolution = 2048;
Stepper myStepper(stepsPerRevolution, 8, 10, 9, 11);

volatile bool shouldRun = false;
volatile long stepCount = 0;

void setup() {
  Wire.begin(0x08);  // I2C slave address
  Wire.onReceive(receiveEvent);  // Master writes
  Wire.onRequest(requestEvent);  // Master reads

  myStepper.setSpeed(10);  // RPM
  Serial.begin(9600);
}

void loop() {
  if (shouldRun) {
    myStepper.step(1);
    stepCount++;
  }
}

void receiveEvent(int howMany) {
  if (howMany < 2) return;  // Expect 2 bytes: [ID, STATE]

  byte cmdID = Wire.read();
  byte state = Wire.read();

  if (cmdID == 0x02) {
    if (state == 0x01) {
      shouldRun = true;
    } else if (state == 0x00) {
      shouldRun = false;
    }
  }
}

void requestEvent() {
  // Respond with 4-byte step count (little-endian)
  Wire.write((byte*)&stepCount, sizeof(stepCount));
}
