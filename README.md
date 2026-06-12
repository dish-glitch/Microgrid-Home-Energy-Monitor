# Home Energy Monitor

**A custom PCB that measures real-time household power consumption (Watts, apparent power (VA), and power factor) and streams live data to a OLED screen.**

![Status](https://img.shields.io/badge/status-in%20progress-yellow)
![License](https://img.shields.io/badge/license-MIT-blue)
![KiCad](https://img.shields.io/badge/PCB-KiCad-blue)
![Platform](https://img.shields.io/badge/platform-ESP32-green)
![Platform](https://img.shields.io/badge/CAD-Autodesk-red)

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

A live dashboard is served over WiFi and accessible from any browser on the network. A small OLED on the device shows readings which i plan on adding into my kitchen 

---

## How It Works (Technical)

The SCT-013 current clamp outputs a small AC signal that mirrors the current in the wire it's clamped around. That signal has three problems before the ESP32 can read it:

1. **It swings negative** — the ESP32 ADC only reads 0–3.3V. An op-amp bias circuit lifts the signal to a 1.65V midpoint so it never goes below 0V.
2. **It's in the wrong units** — a burden resistor converts current to a readable voltage via Ohm's Law (V = I × R).
3. **It carries noise** — an RC low-pass filter passes 60Hz but blocks high-frequency interference.

The ESP32 samples the clean signal at high frequency and runs RMS math in firmware to extract true power values. Power factor is computed from the phase difference between the voltage and current waveforms.

---

## Hardware

| Component | Part | Qty | Est. Cost |
|---|---|---|---|
| Microcontroller | ESP32-WROOM-32 module | 1 | ~$5 |
| Current sensor | SCT-013-000 (100A) | 2 | ~$7 ea |
| Op-amp | MCP6002 | 1 | ~$0.50 |
| Burden resistor | 33Ω 1% | 2 | ~$0.10 ea |
| Bias resistors | 10kΩ | 4 | ~$0.05 ea |
| Filter capacitors | 10µF + 100nF | 4 | ~$0.20 |
| Audio jack | 3.5mm stereo panel mount | 2 | ~$0.50 ea |
| Display | SSD1306 OLED 128x64 | 1 | ~$4 |
| USB connector | USB-C breakout | 1 | ~$0.50 |
| PCB fabrication | JLCPCB (5 boards) | 1 | ~$20 |
| Enclosure | 3D printed (PLA) | 1 | ~$3 |
| **Total** | | | **~$50** |

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
| — | KiCad schematic complete |
| — | PCB layout complete, Gerbers exported |
| — | PCBs ordered from JLCPCB |
| — | Enclosure designed and printed |
| — | PCBs arrived, soldering complete |
| — | Firmware complete, first power readings |
| — | Dashboard live, full system working |

---

## Status

- [ ] KiCad schematic
- [ ] PCB layout
- [ ] PCB fabrication (JLCPCB)
- [ ] 3D enclosure design
- [ ] Firmware — ADC sampling + RMS math
- [ ] Firmware — power factor calculation
- [ ] WiFi dashboard
- [ ] Full system test

---

## License

MIT — use, modify, share freely. See [LICENSE](LICENSE).
