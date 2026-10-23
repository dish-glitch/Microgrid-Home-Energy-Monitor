// Bring-up test for a freshly assembled board. No sensors or extra libraries needed.
// Blinks D2, scans I2C for the OLED, reads the BOOT button and prints the three ADC inputs.

#include <Wire.h>

#define PIN_CT1 34
#define PIN_CT2 35
#define PIN_VOLTAGE 36
#define PIN_LED 2
#define PIN_BOOT 0

int readAvgMv(int pin) {
  long sum = 0;
  for (int i = 0; i < 64; i++) sum += analogReadMilliVolts(pin);
  return sum / 64;
}

void scanI2C() {
  Serial.println("I2C scan:");
  int found = 0;
  for (byte addr = 1; addr < 127; addr++) {
    Wire.beginTransmission(addr);
    if (Wire.endTransmission() == 0) {
      Serial.printf("  found device at 0x%02X%s\n", addr, (addr == 0x3C || addr == 0x3D) ? " (OLED)" : "");
      found++;
    }
  }
  if (!found) Serial.println("  nothing found (OLED not connected or SDA/SCL wiring wrong)");
}

void setup() {
  Serial.begin(115200);
  delay(500);
  Serial.println("\n=== Board test ===");
  pinMode(PIN_LED, OUTPUT);
  pinMode(PIN_BOOT, INPUT_PULLUP);
  analogSetAttenuation(ADC_11db); // full 0-3.3V range
  Wire.begin(21, 22);
  scanI2C();
}

void loop() {
  digitalWrite(PIN_LED, !digitalRead(PIN_LED));
  Serial.printf("CT1: %4d mV   CT2: %4d mV   VOLT: %4d mV   BOOT: %s\n",
                readAvgMv(PIN_CT1), readAvgMv(PIN_CT2), readAvgMv(PIN_VOLTAGE),
                digitalRead(PIN_BOOT) == LOW ? "PRESSED" : "released");
  delay(500);
}
