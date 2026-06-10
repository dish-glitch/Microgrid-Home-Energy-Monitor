# Hardware

KiCad schematic and PCB layout files for the Home Energy Monitor.

## Contents (added as project progresses)

- `energy-monitor.kicad_pro` — KiCad project file
- `energy-monitor.kicad_sch` — Schematic
- `energy-monitor.kicad_pcb` — PCB layout
- `gerbers/` — Fabrication files for JLCPCB

## Design Notes

- 2-layer PCB
- Analog front-end: burden resistor + op-amp mid-rail bias + RC low-pass filter per channel
- Two CT sensor input channels (3.5mm jacks)
- ESP32-WROOM-32 module
- SSD1306 OLED via I2C
- USB-C power input
