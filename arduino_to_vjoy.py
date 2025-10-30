import serial
from pyvjoy import VJoyDevice, HID_USAGE_X

# === CONFIGURE ===
ARDUINO_COM = 'COM5'    # your COM port
BAUD_RATE = 115200
VJOY_DEVICE_ID = 1

# === Connect ===
ser = serial.Serial(ARDUINO_COM, BAUD_RATE)
j = VJoyDevice(VJOY_DEVICE_ID)

# === vJoy range constants ===
VJOY_MIN = 1
VJOY_MAX = 32767
VJOY_CENTER = (VJOY_MIN + VJOY_MAX) // 2

print("✅ 1:1 Steering Bridge Started")

def map_range(x, in_min, in_max, out_min, out_max):
    return int((x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min)

while True:
    try:
        line = ser.readline().decode().strip()
        if line:
            angle = int(line)               # −450 → +450
            vjoy_val = map_range(angle * 2, -450, 450, VJOY_MIN, VJOY_MAX)
            j.set_axis(HID_USAGE_X, vjoy_val)
    except Exception as e:
        print("Error:", e)
