# Gerbers

Fabrication files for JLCPCB — generated from KiCad 9 after final DRC pass.

> **Status:** Generated June 14, 2026. Ready to upload to JLCPCB.

## Ordering from JLCPCB

1. Zip all files in this folder
2. Upload the zip at [jlcpcb.com](https://jlcpcb.com)
3. Recommended settings:
   - Layers: 2
   - PCB Dimensions: 130mm × 73mm
   - PCB Thickness: 1.6mm
   - Surface Finish: HASL (lead-free)
   - Copper Weight: 1oz
   - Quantity: 5 (minimum, ~$2 base price)

## Files

| File | Description |
|---|---|
| `Microgrid-Home-Energy-Monitor-F_Cu.gtl` | Front copper layer |
| `Microgrid-Home-Energy-Monitor-B_Cu.gbl` | Back copper layer |
| `Microgrid-Home-Energy-Monitor-F_Mask.gts` | Front solder mask |
| `Microgrid-Home-Energy-Monitor-B_Mask.gbs` | Back solder mask |
| `Microgrid-Home-Energy-Monitor-F_Silkscreen.gto` | Front silkscreen |
| `Microgrid-Home-Energy-Monitor-B_Silkscreen.gbo` | Back silkscreen |
| `Microgrid-Home-Energy-Monitor-F_Paste.gtp` | Front solder paste |
| `Microgrid-Home-Energy-Monitor-B_Paste.gbp` | Back solder paste |
| `Microgrid-Home-Energy-Monitor-Edge_Cuts.gm1` | Board outline |
| `Microgrid-Home-Energy-Monitor-PTH.drl` | Plated through-hole drill file |
| `Microgrid-Home-Energy-Monitor-NPTH.drl` | Non-plated through-hole drill file |
| `Microgrid-Home-Energy-Monitor-job.gbrjob` | KiCad Gerber job file |

## How to Regenerate (KiCad 9)

1. Open `Microgrid-Home-Energy-Monitor.kicad_pcb`
2. File → Fabrication Outputs → Gerbers
3. Output folder: `hardware/gerbers/`
4. Layers: F.Cu, B.Cu, F.Paste, B.Paste, F.Silkscreen, B.Silkscreen, F.Mask, B.Mask, Edge.Cuts
5. Check "Use Protel filename extensions"
6. Click Plot, then Generate Drill Files in same dialog
