# Design Decisions

Engineering decisions made during development and why.

---

## Why SCT-013-000 (100A version)?

The SCT-013-000 is a current output CT (not voltage output). It outputs 0–50mA secondary current for 0–100A primary current. A burden resistor converts this to a voltage the ADC can read.

The 100A range covers typical US residential circuits (most breakers are 15A or 20A per circuit, with a 200A main). The 0–50mA output is easy to condition with a simple passive burden resistor.

**Why not a voltage-output CT?** Voltage-output CTs have internal burden resistors and output ±1V. They require a burden resistor to be removed or bypassed when the clamp is open, and the fixed output range is less flexible. Current-output gives more control over the signal chain.

---

## Why 33Ω burden resistor?

At full scale (100A primary → 50mA secondary):

```
V_peak = I_secondary_peak × R_burden
V_peak = (50mA × √2) × 33Ω = 2.33V peak
```

With the 1.65V bias, the signal swings from ~0V to ~3.3V — exactly filling the ESP32 ADC range without clipping. Any larger and we'd clip; any smaller and we'd waste ADC resolution.

---

## Why MCP6002 op-amp?

Requirements: single-supply 3.3V rail-to-rail input/output, low offset voltage, dual channel (two CT inputs on one chip), DIP package for hand soldering.

MCP6002 meets all of these. It's rated for 1.8V–6V single supply, rail-to-rail I/O, 900µV max offset, dual package (DIP-8). Industry standard for this exact application.

---

## Why SENSOR_VP (GPIO36) for voltage sensing?

GPIO36 (SENSOR_VP) is an input-only ADC pin. It has no internal pull-up or pull-down resistors, making it the lowest-noise ADC input on the ESP32. Voltage measurements are very sensitive to noise, so using the cleanest available pin improves power factor calculation accuracy.

---

## Why AMS1117 instead of a switching regulator?

A buck converter (switching regulator) would be more efficient but introduces switching noise at 100kHz+ that can couple into the analog measurement circuitry. Since the CT sensor signals are at 60Hz, high-frequency noise from a switcher is harder to filter.

The AMS1117 linear regulator dissipates the extra voltage as heat instead of switching. At the current draw of this project (~300mA max), the efficiency loss (~0.5W) is acceptable, and the board stays quiet on the analog side.

---

## Why 4.7kΩ I2C pull-ups?

I2C requires open-drain pull-up resistors. Pull-up value affects:
- Rise time: lower R = faster rise but more current draw
- Range: must keep logic high above 0.7×VCC with capacitive loading

At 3.3V with an SSD1306 OLED (expected bus capacitance ~20pF), 4.7kΩ gives:
```
Rise time τ = R × C = 4700 × 20pF = 94ns
```
Well within the 1000ns maximum for standard-mode I2C (100kHz). 4.7kΩ is the standard recommendation in the I2C spec for 3.3V systems.

---

## Why USB-C instead of micro-USB?

USB-C is the current standard. The GCT USB4085 is a low-cost SMD connector that uses 5.1kΩ resistors on CC1 and CC2 to identify the board as a USB device — any USB-C charger will supply 5V/500mA. No USB 3.x or Power Delivery negotiation needed.

Micro-USB connectors are being phased out and are mechanically weaker (the port is a known failure point on handheld devices). Edge-mounted USB-C is more robust for a wall-mounted energy monitor.

---

## Why no switching on the CT sensor inputs?

CT sensors must never be open-circuited while clamped around a live wire. When the secondary is open, the transformer tries to maintain the turns-ratio voltage — which can be dangerously high. 

The 3.5mm audio jack input keeps the burden resistor always connected across the CT output when a cable is plugged in. When no cable is plugged in (sleeve disconnected), the jack shorts tip-to-sleeve via the switch contact — keeping the CT secondary loaded. This is a known-safe connection method for CT sensors using TRS audio jacks.
