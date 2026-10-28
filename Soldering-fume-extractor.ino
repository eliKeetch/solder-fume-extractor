// ESP32-C3 Super Mini fan PWM with potentiometer

const int potPin = 0;   // GPIO0 = potentiometer middle pin
const int fanPin = 4;   // GPIO4 = MOSFET gate

const int pwmFreq = 25000;   // 25 kHz
const int pwmResolution = 8; // 0-255

void setup() {
  pinMode(potPin, INPUT);

  bool ok = ledcAttach(fanPin, pwmFreq, pwmResolution);
  if (!ok) {
    while (true) {
      delay(1000);
    }
  }
}

void loop() {
  int potValue = analogRead(potPin);   // usually 0-4095 on ESP32
  int duty = map(potValue, 0, 4095, 0, 255);

  // full off at the bottom
  if (potValue < 120) {
    duty = 0;
  }

  // keep fan from stalling in low range
  if (duty > 0 && duty < 80) {
    duty = 80;
  }

  ledcWrite(fanPin, duty);

  delay(10);
}