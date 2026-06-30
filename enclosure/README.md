# Enclosure

3D printed two-part shell designed in Fusion 360 by [@hummos430](https://github.com/hummos430). Provides access to all external connectors while protecting the PCB and managing heat from the AMS1117 regulator.

> **Status:** Design complete — files committed. OLED window to be added after screen arrives. PCB mounted with double-sided tape (v1 build; mounting holes planned for PCB v2).

---

## Design

Two-part assembly:
- **Bottom tray** — holds PCB, contains vent pattern below AMS1117, CT jack holes and USB-C cutout on walls
- **Top lid** — LED holes, boot/reset button cutouts, decorative vent pattern

### Dimensions
- **Total height:** 20mm
- **Footprint:** ~136mm × 79mm (130mm × 73mm PCB + 3mm clearance each side)
- **Wall thickness:** 2mm

### External Cutouts

| Feature | Wall | Size |
|---|---|---|
| USB-C port (J4) | Right | 10mm × 4.5mm |
| CT sensor jack 1 (J1) | Front/Bottom | ⌀6.5mm |
| CT sensor jack 2 (J2) | Front/Bottom | ⌀6.5mm |
| OLED 0.96" window (J3) | Top lid | 22mm × 12mm — pending |
| ZMPT101B connector (J6) | Side | Rectangular slot |
| Power LED (D1) | Top lid | ⌀5.2mm |
| Status LED (D2) | Top lid | ⌀5.2mm |
| Reset button (SW1) | Top lid | ⌀4mm recessed |
| Boot button (SW2) | Top lid | ⌀4mm recessed |

Programming header (J5) is internal — accessible by removing lid only.

---

## ESP32 Antenna

The ESP32-WROOM-32 antenna is on the short end of the module (farthest from solder pads). The enclosure has vent slots on the wall nearest the antenna — no solid plastic within 5mm of the antenna tip.

---

## Heat Dissipation

The AMS1117-3.3 regulator dissipates approximately 0.5W at normal load (~300mA). Thermal design:

- **Bottom vent pattern** — decorative cutouts in the floor provide airflow beneath U3
- **Side clearance** — gap between PCB edge and enclosure wall for lateral airflow
- **Open internal cavity** — no foam or insulation inside
- **Material: PETG-CF** — carbon fiber PETG, stiffer and more heat resistant than standard PETG or PLA

---

## Print Settings

| Setting | Value |
|---|---|
| Material | PETG-CF (used) |
| Layer height | 0.2mm |
| Infill | 20% gyroid |
| Perimeters | 3 |
| Supports | No |
| Bed temp | 85°C |
| Nozzle temp | 235°C |

---

## Assembly

- PCB secured with double-sided foam tape (v1)
- 4× M3×8mm screws (lid to tray)

---

## Files

| File | Description |
|---|---|
| `HomecurrentMoniter_BottomPlateHCM updated.f3d` | Fusion 360 source — bottom tray |
| `HomecurrentMoniter_Top Plate HCM UPDATED.f3d` | Fusion 360 source — top lid |
| `HomecurrentMoniter_BottomPlateHCM updated.stl` | Print file — bottom tray |
| `HomecurrentMoniter_Top Plate HCM UPDATED.stl` | Print file — top lid |

**Pictures**

<img width="1129" height="676" alt="Screenshot 2026-06-15 163151" src="https://github.com/user-attachments/assets/75925e14-7fbb-44e5-b3f4-d2514e1974b1" />
