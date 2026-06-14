# Firmware

ESP32 firmware written in C++ using the Arduino framework. Reads dual CT sensor channels and a ZMPT101B voltage sensor, computes real power, apparent power, and power factor, displays live readings on an SSD1306 OLED, and serves a WiFi dashboard.

> **Status:** In development — PCB fabrication completing first.

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
│  WiFi ──► AsyncWebServer ──► Live dashboard          │
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
| `ESPAsyncWebServer` | Non-blocking WiFi server | GitHub |
| `AsyncTCP` | Required by ESPAsyncWebServer | GitHub |

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
1. Install ESP32 board support: `https://dl.espressif.com/dl/package_esp32_index.json`
2. Select board: `ESP32 Dev Module`
3. Install all dependencies via Library Manager
4. Set upload speed: `921600`
5. Flash via J5 programming header (FTDI232 or CP2102 USB-serial adapter)

**PlatformIO (recommended):**
```bash
pio run --target upload
```

---

## WiFi Dashboard

After flashing, the ESP32 hosts a web server on port 80. Connect to the same WiFi network and navigate to the device's IP address (printed to serial on boot).

Dashboard shows:
- Real-time watts per channel
- Apparent power (VA)
- Power factor
- Cumulative kWh
- Live waveform plot (planned)
