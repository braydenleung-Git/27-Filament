const int pwmPin = 9;  // Must use Timer1 PWM pin (pin 9 or 10 on Uno)

const int freqCount = 4;
const unsigned int frequencies[freqCount] = {5000, 10000, 20000, 50000};  // in Hz
int currentFreqIndex = 0;

void setup() {
  pinMode(pwmPin, OUTPUT);
  setPwmFrequency(frequencies[currentFreqIndex]);
}

void loop() {
  // Just demo: change frequency every 5 seconds
  static unsigned long lastSwitch = 0;
  if (millis() - lastSwitch > 5000) {
    currentFreqIndex = (currentFreqIndex + 1) % freqCount;
    setPwmFrequency(frequencies[currentFreqIndex]);
    lastSwitch = millis();
  }
}

// Function to configure Timer1 for desired frequency
void setPwmFrequency(unsigned int frequency) {
  // Stop Timer1
  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1  = 0;

  // Set mode: Fast PWM with TOP set by ICR1
  TCCR1A |= (1 << COM1A1) | (1 << WGM11);
  TCCR1B |= (1 << WGM13) | (1 << WGM12) | (1 << CS10);  // No prescaler

  unsigned long top = (16000000UL / frequency) - 1;  // 16MHz clock, no prescale

  ICR1 = top;              // Set TOP value for frequency
  OCR1A = top / 2;         // 50% duty cycle
}
