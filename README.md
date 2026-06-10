# Home Energy Monitor

**A custom PCB that measures real-time household power consumption — Watts, apparent power (VA), and power factor — and streams live data to a WiFi dashboard.**

![Status](https://img.shields.io/badge/status-in%20progress-yellow)
![License](https://img.shields.io/badge/license-MIT-blue)
![KiCad](https://img.shields.io/badge/PCB-KiCad-blue)
![Platform](https://img.shields.io/badge/platform-ESP32-green)

---

## Why I Built This

In February 2021, over 4.5 million Texas homes lost power during the ERCOT grid failure. I was one of them. Every hotel was booked as families scrambled for heat — it was one of the hardest winters I can remember. I wanted to understand how it actually happened.

The core problem wasn't just frozen generators. Grid operators had almost no real-time view into household power consumption. They couldn't see how demand was shifting minute by minute as millions of people cranked their heaters at the same time. They were managing a statewide crisis without the data to make precise decisions.

I want to build that data layer — starting at the household level. This project is my attempt to understand how power is actually measured at the circuit level, and to build something real around that knowledge.

---

## What It Does

Non-invasive current transformer (CT) sensors clip around household wires inside a breaker box — no contact with live wiring. The custom PCB conditions the signal from the sensors and feeds it to an ESP32 microcontroller, which computes:

- **Real Power (Watts)** — actual energy consumed
- **Apparent Power (VA)** — total load on the circuit
- **Power Factor** — how efficiently the home is drawing power
- **Cumulative kWh** — running energy usage over time

A live dashboard is served over WiFi and accessible from any browser on the network. A small OLED on the device shows readings without needing a phone.

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
| Burden resistor | 10Ω 1% | 2 | ~$0.10 ea |
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
| June 2026 | Project started. Repository initialized. |
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
