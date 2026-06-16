# Home Energy Monitor

**A custom PCB that measures real-time household power consumption (Watts, apparent power (VA), and power factor) and streams live data to a OLED screen.**

![Status](https://img.shields.io/badge/status-in%20progress-yellow)
![License](https://img.shields.io/badge/license-MIT-blue)
![KiCad](https://img.shields.io/badge/PCB-KiCad-blue)
![Platform](https://img.shields.io/badge/platform-ESP32-green)
![Platform](https://img.shields.io/badge/CAD-Autodesk-red)

---

## Schematic Preview



<img width="634" height="476" alt="image" src="https://github.com/user-attachments/assets/2f8c8e56-fbea-4777-b9e2-88b52e13e491" />

---

## PCB Preview

<img width="1027" height="564" alt="image" src="https://github.com/user-attachments/assets/f797b869-352d-47de-808c-f22c5249dbf1" />



## Enclosure Preview

![Enclosure render](docs/photos/image-1781640720901.png)
![Enclosure top view](docs/photos/image-1781640738088.png)

---

## Why I Built This

In February 2021, over 4.5 million Texas homes lost power in freezing temperatures during a power grid failure. I was one of them, the winter was hard with all hotels being booked as people scrambled to get heat. It was a very hard winter with our apartment getting to around 60 degrees Fahrenheit. I wanted to understand why the grid failure happened and came to the conclusion, The problem was that grid operators had almost no real-time view into household consumption of power. They didn't have the data to see the demand of power was changing minute by minute as more people in homes turned on their heaters to warm their homes. I want to understand how power is measured, how the grid sees demand so I will try to build a custom PCB that clips non-invasive current transformer sensors around wires and measure real-time power usage I would like it to measure Watts. Apparent power (VA) and Power factor.



---

## What It Does

Non-invasive current transformer (CT) sensors clip around household wires inside a breaker box(does not touch any live wires). The custom PCB conditions the signal from the sensors and feeds it to an ESP32 microcontroller, which measures:

- **Real Power (Watts)** 
- **Apparent Power (VA)**
- **Power Factor** 
- **Cumulative kWh** 

A live dashboard is served over WiFi and accessible from any browser on the network. A small OLED on the device shows readings.
---

## How It Works

The SCT-013 current clamp outputs a small AC signal that mirrors the current in the wire it's clamped around. That signal has three problems before the ESP32 can read it:

1. **It swings negative** — the ESP32 ADC only reads 0–3.3V. An op-amp bias circuit lifts the signal to a 1.65V midpoint so it never goes below 0V.
2. **It's in the wrong units** — a burden resistor converts current to a readable voltage via Ohm's Law (V = I × R).
3. **It carries noise** — an RC low-pass filter passes 60Hz but blocks high-frequency interference.

The ESP32 samples the clean signal at high frequency and runs RMS math in firmware to extract true power values. Power factor is computed from the phase difference between the voltage and current waveforms.

---

## Hardware

| Component | Part | Qty | Est. Cost | Link |
|---|---|---|---|---|
| Microcontroller | ESP32-WROOM-32 module | 1 | ~$5 | [Amazon](https://www.amazon.com/ESP-WROOM-32D-ESP-32-Bluetooth-Module-ESP32-WROOM-32D/dp/B085BNHPW5) |
| Current sensor | SCT-013-000 (100A) | 2 | ~$7 ea | [Amazon](https://www.amazon.com/YHDC-Transformer-SCT013-000-100A-50mA/dp/B01EFS7QUE) |
| Op-amp | MCP6002 | 1 | ~$0.50 | [Amazon](https://www.amazon.com/MICROCHIP-MCP6002-I-MCP6002-Operational-Amplifier/dp/B06Y6BPF51) |
| Burden resistor | 33Ω 1% | 2 | ~$0.10 ea | [Amazon](https://www.amazon.com/33-ohm-Metal-Resistors-Tolerance/dp/B07DHGJXMN) |
| Bias resistors | 10kΩ | 4 | ~$0.05 ea | [Amazon](https://www.amazon.com/Resistor-Tolerance-Resistors-Limiting-Certificated/dp/B08QRJZ82J) |
| Filter capacitors | 10µF + 100nF | 4 | ~$0.20 | [Amazon](https://www.amazon.com/ALLECIN-Electrolytic-Capacitor-Assortment-Kit/dp/B0C1VBXCQM) |
| Audio jack | 3.5mm stereo panel mount | 2 | ~$0.50 ea | [Amazon](https://www.amazon.com/Lsgoodcare-Connector-Terminals-Nuts-3-5MM-Headphone/dp/B013AP77T8) |
| Display | SSD1306 OLED 128x64 | 1 | ~$4 | [Amazon](https://www.amazon.com/Hosyond-Display-Self-Luminous-Compatible-Raspberry/dp/B09C5K91H7) |
| USB connector | USB-C breakout | 1 | ~$0.50 | [Amazon](https://www.amazon.com/MECCANIXITY-Breakout-Female-Connection-Connector/dp/B0CD7WG2WD) |
| PCB fabrication | JLCPCB (5 boards) | 1 | ~$20 | [JLCPCB](https://jlcpcb.com) |
| Enclosure | 3D printed (PETG-CF) | 1 | ~$3 | filament on hand |
| **Total** | | | **~$50** | |

---

## Repository Structure

```
home-energy-monitor/
├── hardware/        # KiCad schematic, PCB layout, Gerber files
├── firmware/        # ESP32 Arduino code
├── enclosure/       # FreeCAD source + STL files for 3D printing
└── docs/
    └── photos/      # Build progress photos
```

---

## Build Log

| Date | Milestone |
|---|---|
| June 10, 2026 | Project started. Repository initialized. |
| June 11, 2026 | KiCad schematic started — analog front-end both CT channels complete |
| June 13, 2026 | KiCad schematic complete — ERC passes clean, all components wired |
| June 14, 2026 | PCB layout complete — all components placed, routed, ground plane poured, DRC clean |
| June 14, 2026 | Gerbers exported and committed — ready for JLCPCB upload |
| June 14, 2026 | Firmware written — RMS sampling, power math, OLED display, kWh accumulator. Verified on Wokwi simulator. |
| June 15, 2026 | WiFi dashboard complete — ESP32 serves live readings over HTTP, JavaScript polls every second |
| June 16, 2026 | 3D enclosure designed by [@hummos430](https://github.com/hummos430) in Fusion 360 — files committed |
| June 16, 2026 | Stardance funding submitted — S tier $150 |
| — | PCBs ordered from JLCPCB |
| — | PCBs arrived, soldering complete |
| — | Firmware calibrated, first real power readings |
| — | Dashboard live, full system working |

---

## Simulation

Test the firmware logic without hardware — runs in browser:

[![Wokwi Simulation](https://img.shields.io/badge/Wokwi-Run%20Simulation-green?logo=data:image/svg+xml;base64,PHN2ZyB4bWxucz0iaHR0cDovL3d3dy53My5vcmcvMjAwMC9zdmciIHZpZXdCb3g9IjAgMCAyNCAyNCI+PHBhdGggZmlsbD0id2hpdGUiIGQ9Ik04IDV2MTRsMTEtN3oiLz48L3N2Zz4=)](https://wokwi.com/projects/466868484916087809)

Simulates dual CT sensor readings, RMS power math, serial output, and OLED display on a virtual ESP32. CH1 uses hardcoded test values (120V, 5A, 550W, PF 0.92) to verify the signal chain and kWh accumulator logic.

---

## Status

- [x] KiCad schematic
- [x] PCB layout
- [x] Firmware — ADC sampling + RMS math
- [x] Firmware — power factor calculation
- [ ] PCB fabrication (JLCPCB)
- [x] 3D enclosure design
- [x] WiFi dashboard
- [ ] Full system test

---

## License

MIT — use, modify, share freely. See [LICENSE](LICENSE).
