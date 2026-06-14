# Enclosure

3D printed two-part shell designed in Fusion 360. Provides access to all external connectors while protecting the PCB and managing heat from the AMS1117 regulator.

> **Status:** In development — PCB dimensions confirmed, modeling in progress.

---

## Design

Two-part snap/screw assembly:
- **Bottom tray** — holds PCB on 5mm standoffs, contains vent slots below AMS1117
- **Top lid** — OLED window, LED holes, button access cutouts

### External Cutouts

| Feature | Wall | Size |
|---|---|---|
| USB-C port (J4) | Right | 9mm × 4mm |
| CT sensor jack 1 (J1) | Bottom | ⌀6.5mm |
| CT sensor jack 2 (J2) | Bottom | ⌀6.5mm |
| OLED cable (J3) | Top | Rectangular slot |
| ZMPT101B connector (J6) | Top | Rectangular slot |
| Power LED (D1) | Top lid | ⌀3mm |
| Status LED (D2) | Top lid | ⌀3mm |
| Reset button (SW1) | Top lid | ⌀4mm recessed |
| Boot button (SW2) | Top lid | ⌀4mm recessed |

Programming header (J5) is internal — accessible by removing lid only.

---

## Heat Dissipation

The AMS1117-3.3 regulator dissipates approximately 0.5W at normal load (~300mA). Thermal design:

- **Bottom vent slots** — 6× slots (1mm × 15mm) in the floor directly beneath U3
- **Side clearance** — 1mm gap between PCB edge and enclosure wall for lateral airflow
- **Open internal cavity** — no foam or insulation inside
- **Material: PETG** — preferred over PLA for heat resistance near the regulator

---

## Print Settings

| Setting | Value |
|---|---|
| Material | PETG (preferred) or PLA |
| Layer height | 0.2mm |
| Infill | 20% gyroid |
| Perimeters | 3 |
| Supports | No |
| Bed temp | 85°C (PETG) |
| Nozzle temp | 235°C (PETG) |

---

## Assembly Hardware

- 4× M3×8mm screws (lid to tray)
- 4× M3 brass heat-set inserts (in PCB standoff posts)
- 4× M3×6mm screws (PCB to standoffs)

---

## Files

| File | Description |
|---|---|
| `energy-monitor-case-bottom.f3d` | Fusion 360 source — bottom tray |
| `energy-monitor-case-top.f3d` | Fusion 360 source — top lid |
| `energy-monitor-case-bottom.stl` | Print file — bottom tray |
| `energy-monitor-case-top.stl` | Print file — top lid |
