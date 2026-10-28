# Firmware

The firmware is written in C++ using the Arduino framework and runs on the ESP32. It samples two CT current sensors and a ZMPT101B voltage sensor to calculate real power, apparent power, power factor, and cumulative energy usage. Live measurements are displayed on an SSD1306 and are also available through a built-in WiFi dashboard.

> **Status:** Running on the assembled board (rev 1). OLED, both CT channels and the bring-up tests are verified; real-sensor calibration is next.

---

## Architecture

```
┌─────────────────────────────────────────────────────┐
│                     ESP32                            │
│                                                      │
│  ADC (GPIO34) ──► CT Channel 1 sampling             │
│  ADC (GPIO35) ──► CT Channel 2 sampling  ──► RMS   ──► Power math
│  ADC (GPIO36) ──► Voltage channel sampling           │
│                                                      │
│  I2C (GPIO21/22) ──► SSD1306 OLED display           │
│  WiFi ──► WebServer ──► Live dashboard               │
└─────────────────────────────────────────────────────┘
```

## Power Calculation

**RMS current** sampled at high frequency over one full 60Hz cycle:

```
I_rms = sqrt( (1/N) * Σ(sample²) )
```

**Real power** (Watts) from instantaneous voltage × current:

```
P = (1/N) * Σ(v[n] * i[n])
```

**Apparent power** (VA):

```
S = V_rms * I_rms
```

**Power factor:**

```
PF = P / S
```

**Cumulative kWh:**

```
kWh += P * (sample_interval_ms / 3600000)
```

---

## Dependencies

| Library | Purpose | Install via |
|---|---|---|
| `EmonLib` | RMS sampling + power math | Arduino Library Manager |
| `Adafruit SSD1306` | OLED driver | Arduino Library Manager |
| `Adafruit GFX` | Graphics primitives | Arduino Library Manager |
| `modbus-esp8266` (by Andre Sarmento Barbosa) | Modbus TCP server (`ModbusIP_ESP8266.h`) — works on ESP32 too | Arduino Library Manager |
| `WiFi` / `WebServer` | WiFi + HTTP dashboard | Built into the ESP32 Arduino core |

---

## Pin Map

| GPIO | Function |
|---|---|
| 34 | ADC CH1 (CT sensor 1) |
| 35 | ADC CH2 (CT sensor 2) |
| 36 (SENSOR_VP) | ADC voltage (ZMPT101B) |
| 21 | I2C SDA (OLED) |
| 22 | I2C SCL (OLED) |
| 2 | Status LED |
| 1 (TX0) | UART TX (programming) |
| 3 (RX0) | UART RX (programming) |

---

## Build & Flash

**Arduino IDE:**
1. Install ESP32 board support: **esp32 by Espressif Systems** in Boards Manager (if it isn't listed, add `https://espressif.github.io/arduino-esp32/package_esp32_index.json` under File → Preferences → Additional boards manager URLs)
2. Select board: `ESP32 Dev Module`
3. Install all dependencies via Library Manager
4. Set upload speed: `921600`
5. **Set `SIMULATION` to `0`** at the top of the sketch — with it at `1` the board
   reports hardcoded Wokwi test values instead of real measurements
6. Set your WiFi SSID/password in the sketch — must be a **2.4 GHz WPA2-Personal** network (a phone hotspot works). WPA2-Enterprise networks such as campus Wi-Fi are not supported, and they usually block device-to-device traffic anyway. Without WiFi the board still runs the OLED and serial output after a 10 s timeout.
7. Flash via the J5 programming header with a CP2102/FTDI adapter: GND→pin 1, TXD→pin 4 (RX0), RXD→pin 3 (TX0), adapter power pins unconnected
8. The board has no auto-reset circuit. When the IDE shows `Connecting...`, hold **BOOT (SW2)**, tap **RESET (SW1)** and release BOOT. After `Hard resetting via RTS pin...`, press **RESET** to start the sketch.

Give the board at least **0.5 A** of supply current — WiFi transmit bursts reach ~250 mA, and a tighter current limit browns out the ESP32.

### Board bring-up test

[`board-test/board-test.ino`](board-test/board-test.ino) needs no sensors or extra libraries. It blinks D2, scans I2C for the OLED, reports the BOOT button and prints the three ADC inputs. On a healthy board with nothing plugged into J1/J2, **CT1 and CT2 both read ≈1650 mV** (the bias midpoint); VOLT floats until the ZMPT101B is connected.

---

## WiFi Dashboard

Once programmed, the ESP32 hosts a web server on port 80. Connect a device to the same WiFi network and open the ESP32's IP address in a web browser. The IP address is printed to the serial monitor during startup.

Dashboard shows:
- Mains voltage (Vrms)
- Channel 1 real power (W) + apparent power (VA)
- Channel 2 apparent power (VA — CH2 has no voltage phase reference, so real W is not available on this channel)
- Power factor (channel 1)
- Cumulative kWh
- Live waveform plot (planned)
