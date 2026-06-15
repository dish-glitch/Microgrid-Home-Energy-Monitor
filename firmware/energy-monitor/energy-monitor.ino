#include "EmonLib.h"
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <WiFi.h>
#include <WebServer.h>


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

const char* WIFI_SSID = "WIFI NAME "; // change <------------------------------
const char* WIFI_PASS = "WIFI PASSWORD"; // change <----------------------------

WebServer server(80);

Adafruit_SSD1306 display(OLED_WIDTH, OLED_HEIGHT, &Wire, -1);

EnergyMonitor ct1;
EnergyMonitor ct2;

float kwh1 = 0.0;//gets energy over time 
float kwh2 = 0.0;//gets energy over time 
unsigned long lastMillis = 0;  // counts up from 0 and does NOT go into the negatives (tracks time)



// ================================================
// --- HTML(web browser) ---
// ================================================

String getDataJSON() {
  String json = "{";
  json += "\"vrms\":"    + String(ct1.Vrms, 1)        + ",";
  json += "\"watts1\":"  + String(ct1.realPower, 1)   + ",";
  json += "\"watts2\":"  + String(ct1.Vrms * ct2.Irms, 1) + ",";
  json += "\"pf\":"      + String(ct1.powerFactor, 2) + ",";
  json += "\"kwh\":"     + String(kwh1 + kwh2, 4);
  json += "}";
  return json;
}

String getDashboardHTML() {
  String html = R"rawhtml(
<!DOCTYPE html>
<html>
<head>
  <title>Energy Monitor</title>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <style>
    body { font-family: sans-serif; background: #111; color: #eee; text-align: center; padding: 20px; }
    h1 { color: #4fc3f7; }
    .card { background: #1e1e1e; border-radius: 12px; padding: 20px; margin: 10px auto; max-width: 400px; }
    .value { font-size: 2em; font-weight: bold; color: #4fc3f7; }
    .label { font-size: 0.9em; color: #aaa; margin-top: 4px; }
  </style>
</head>
<body>
  <h1>Home Energy Monitor</h1>
  <div class="card"><div class="value" id="vrms">--</div><div class="label">Voltage (V)</div></div>
  <div class="card"><div class="value" id="watts1">--</div><div class="label">Channel 1 (W)</div></div>
  <div class="card"><div class="value" id="watts2">--</div><div class="label">Channel 2 (W)</div></div>
  <div class="card"><div class="value" id="pf">--</div><div class="label">Power Factor</div></div>
  <div class="card"><div class="value" id="kwh">--</div><div class="label">Total (kWh)</div></div>
  <script>
    setInterval(() => {
      fetch('/data')
        .then(r => r.json())
        .then(d => {
          document.getElementById('vrms').innerText   = d.vrms   + ' V';
          document.getElementById('watts1').innerText = d.watts1 + ' W';
          document.getElementById('watts2').innerText = d.watts2 + ' W';
          document.getElementById('pf').innerText     = d.pf;
          document.getElementById('kwh').innerText    = d.kwh    + ' kWh';
        });
    }, 1000);
  </script>
</body>
</html>
)rawhtml";
  return html;
}





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


// ================================================
// --- Wifi/server set up ---
// ================================================
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  Serial.print("connecting to wifi");
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }

  Serial.println();
  Serial.print("connected to IP: ");
  Serial.println(WiFi.localIP());

  server.on("/", [](){ 
    server.send(200, "text/html", getDashboardHTML()); 
  });

  server.on("/data", [](){
    server.send(200, "application/json", getDataJSON());
  });
  server.begin();
// ================================================
// --- Time  ---
// ================================================

  lastMillis = millis();
  Serial.println("Set up finished :D");
}


// ================================================
// --- Loop  ---
// ================================================

void loop()
{
  server.handleClient(); 
  ct1.calcVI(20,2000); 
  ct2.calcIrms(1480);
  float Vrms          = ct1.Vrms;             //extract Vrms into Variable
  float Irms1         = ct1.Irms;             //extract Irms into Variable
  float Irms2         = ct2.Irms;             //extract Irms into Variable
  float watts1        = ct1.realPower;        //extract Real Power into variable
  float val1          = ct1.apparentPower;    //extract Apparent Power into variable
  float powerFactor1  = ct1.powerFactor;      //extract Power Factor into Variable
  float watts2 = Vrms * Irms2;                // Approximatione

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
