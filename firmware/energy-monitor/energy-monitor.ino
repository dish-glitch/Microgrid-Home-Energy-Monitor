#include "EmonLib.h"
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
// ================================================
// --- Define ---
// ================================================
#define PIN_CT1 34 
#define PIN_CT2 35
#define PIN_VOLTAGE 36
#define PIN_LED 2

#define ICAL 60.6 // fine tune this when the board arrives ((turns ratio(100A)/burdan(0.05))/33(resistor) = 60.6)
#define VCAL 234.26 // fine ture this when you measure with your multimeter. 
#define PHASE_SHIFT 1.7 // timing diffrence

#define OLED_WIDTH 128 
#define OLED_HEIGHT 64
#define OLED_ADDER 0x3C

Adafruit_SSD1306 display(OLED_WIDTH, OLED_HEIGHT, &Wire, -1);

EnergyMonitor ct1;
EnergyMonitor ct2;

float kwh1 = 0.0;//gets energy over time 
float kwh2 = 0.0;//gets energy over time 
unsigned long lastMillis = 0;  // counts up from 0 and does NOT go into the negatives (tracks time)
// ================================================
// --- set up ---
// ================================================
void setup() {
  Serial.begin(115200);
  pinMode(PIN_LED, OUTPUT);
  digitalWrite(PIN_LED, HIGH);

  ct1.voltage(PIN_VOLTAGE, VCAL, PHASE_SHIFT);
  ct1.current(PIN_CT1, ICAL);
  ct2.current(PIN_CT2, ICAL);

  Wire.begin(21, 22);
  if (!display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDER)) {
    Serial.println("SSD1306 not found");
    while (true) {
      digitalWrite(PIN_LED, !digitalRead(PIN_LED));
      delay(200);
    }
  }

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println("Energy Monitor");
  display.println("Booting up X_X");
  display.display();
  delay(1000);

  lastMillis = millis();
  Serial.println("Set up finished :D");
}
void loop() 
{
  ct1.calcVI(20,2000); 
  ct2.calcIrms(1480);
  float Vrms          = ct1.Vrms;             //extract Vrms into Variable
  float Irms1         = ct1.Irms;             //extract Irms into Variable
  float Irms2         = ct2.Irms;             //extract Irms into Variable
  float watts1        = ct1.realPower;        //extract Real Power into variable
  float val1          = ct1.apparentPower;    //extract Apparent Power into variable
  float powerFactor1  = ct1.powerFactor;      //extract Power Factor into Variable
  float watts2 = Vrms * Irms2;                // Approximation 

  unsigned long now = millis();
  float fullHours = (now - lastMillis) / 3600000.0;
  kwh1 += (watts1 / 1000.0 ) * fullHours;
  kwh2 += (watts2 / 1000.0 ) * fullHours;
  lastMillis = now;

 Serial.printf("V:%.1fV  CH1:%.2fA %.1fW PF:%.2f  CH2:%.2fA %.1fW  kWh:%.4f\n", Vrms, Irms1, watts1, powerFactor1, Irms2, watts2, kwh1 + kwh2);


  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.printf("Voltage: %.1f V", Vrms);
  display.setCursor(0, 16);
  display.printf("CH1: %.1f W  PF %.2f", watts1, powerFactor1);
  display.setCursor(0, 28);
  display.printf("CH2: %.1f W", watts2);
  display.setCursor(0, 44);
  display.printf("Total: %.3f kWh", kwh1 + kwh2);
  display.display();
  delay(500);


  
}
