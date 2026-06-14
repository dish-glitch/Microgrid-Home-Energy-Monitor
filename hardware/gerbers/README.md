# Gerbers

Fabrication files for JLCPCB — generated from KiCad after final DRC pass.

> **Status:** Not yet generated. Will be added before PCB order.

## How to Generate (KiCad 9)

1. Open `Microgrid-Home-Energy-Monitor.kicad_pcb`
2. File → Fabrication Outputs → Gerbers
3. Output folder: `hardware/gerbers/`
4. Layers to include:
   - F.Cu, B.Cu
   - F.Paste, B.Paste
   - F.Silkscreen, B.Silkscreen
   - F.Mask, B.Mask
   - Edge.Cuts
5. Check "Use Protel filename extensions"
6. Generate Drill Files in same dialog
7. Zip the folder and upload to jlcpcb.com

## Files (after generation)

| File | Description |
|---|---|
| `*.gtl` | Front copper |
| `*.gbl` | Back copper |
| `*.gts` | Front solder mask |
| `*.gbs` | Back solder mask |
| `*.gto` | Front silkscreen |
| `*.gbo` | Back silkscreen |
| `*.gtp` | Front paste |
| `*.gbp` | Back paste |
| `*.gko` | Board outline |
| `*.drl` | Drill file |
