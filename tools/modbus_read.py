"""
Modbus TCP client for the Home Energy Monitor.
Reads all 8 holding registers from the ESP32 and decodes them.

No external libraries needed - pure Python (socket + struct).
Your laptop must be on the SAME network as the ESP32 (the iPhone hotspot).

Run:  python modbus_read.py
"""

import socket
import struct

# ---- CHANGE THIS to your ESP32's IP (from the Serial Monitor) ----
ESP32_IP = "172.20.10.8"
PORT = 502
# ------------------------------------------------------------------

# Build a Modbus TCP request: Function Code 3 (Read Holding Registers),
# read 8 registers starting at address 0.
#   Transaction ID, Protocol ID, Length, Unit ID, FC, Start addr, Qty
request = struct.pack(">HHHBBHH", 1, 0, 6, 1, 3, 0, 8)

sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
sock.settimeout(5)
sock.connect((ESP32_IP, PORT))
sock.send(request)
response = sock.recv(1024)
sock.close()

# Response layout: 7-byte MBAP header + FC (1) + byte count (1) + data.
# So the 8 registers (16 bytes) start at byte 9.
regs = struct.unpack(">8H", response[9:9 + 16])

print("Raw registers:", regs)
print("-" * 34)
print(f"Voltage:         {regs[0] / 10:.1f} V")
print(f"Current CH1:     {regs[1] / 100:.2f} A")
print(f"Real Power CH1:  {regs[2]} W")
print(f"Apparent CH1:    {regs[3]} VA")
print(f"Power Factor:    {regs[4] / 100:.2f}")
print(f"Total Energy:    {regs[5] / 10:.1f} kWh")
print(f"Current CH2:     {regs[6] / 100:.2f} A")
print(f"Real Power CH2:  {regs[7]} W")
