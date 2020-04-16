#!/usr/bin/env python3
import serial
if __name__ == '__main__':
    ser = serial.Serial('/dev/ttyUSB0', 9600, timeout=1)
    ser.flush()
    while True:
        ser.write(b"<L4R4>")
        if ser.in_waiting > 0:
            try:
                line = ser.readline().decode('utf-8').rstrip()
                print(line)
            # sometimes when reading from serial it gets a weird character that utf-8 cant decode
            except UnicodeDecodeError:
                print("error in reading")
            