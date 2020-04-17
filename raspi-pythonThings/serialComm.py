#!/usr/bin/env python3
import serial

def readFromSerial():
    try:
        line = ser.readline().decode('utf-8').rstrip()
        print(line)
        # sometimes when reading from serial it gets a weird character that utf-8 cant decode
    except UnicodeDecodeError:
        print("error in reading")

def sendMotorCommand(leftSpeed, rightSpeed):
    s = "<L"+str(leftSpeed)+"R"+str(rightSpeed)+">"
    #print(s)
    ser.write(s.encode('utf-8'))

if __name__ == '__main__':
    ser = serial.Serial('/dev/ttyUSB0', 9600, timeout=1)
    ser.flush()
    timer = 0
    while True:
        sendMotorCommand(5,6)
        if ser.in_waiting > 0:
            readFromSerial()
            
            
