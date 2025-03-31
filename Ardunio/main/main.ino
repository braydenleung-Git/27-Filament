#include <Wire.h>

const int ledPin = 13;

volatile byte command = 0;
volatile byte value = 0;
volatile byte status = 0;
volatile byte result = 0;

void setup() {
  Wire.begin(0x8);
  Wire.onReceive(receiveEvent);
  Wire.onRequest(requestEvent);

  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);
}

void loop() {
  if (status == 0) {
    switch (command) {
      case 0x01:  // Turn LED ON/OFF
        if (value == 1) {
          digitalWrite(ledPin, HIGH);
          result = 1;
        } else {
          digitalWrite(ledPin, LOW);
          result = 0;
        }
        break;

      case 0x02:  // Blink LED value times
        for (int i = 0; i < value; i++) {
          digitalWrite(ledPin, HIGH);
          delay(200);
          digitalWrite(ledPin, LOW);
          delay(200);
        }
        result = value;
        break;

      // Add more cases here for new commands

      default:
        result = 0xFF;  // Unknown command
        break;
    }

    status = 1;  // Ready to report back
  }
}

void receiveEvent(int howMany) {
  if (howMany >= 2) {
    command = Wire.read();
    value = Wire.read();
    status = 0;  // Reset status to indicate "working"
  }
}

void requestEvent() {
  Wire.write(status);  // Byte 0: status (0 or 1)
  Wire.write(result);  // Byte 1: result or data
}
