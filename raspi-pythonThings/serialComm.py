#!/usr/bin/env python3
import serial
import time
import threading

def readFromSerial():
    while True:
        
        if ser.in_waiting > 0:
            try:
                line = ser.readline().decode('utf-8').rstrip()
                #print(line)
            
                #some lines are just blank so skip them
                if(line != ""):
                    arduinoRobot.updateIDs(line)
                # sometimes when reading from serial it gets a weird character that utf-8 cant decode
            except UnicodeDecodeError:
                print("error in reading")

def sendMotorCommand(leftSpeed, rightSpeed):
    s = "<L"+str(leftSpeed)+"R"+str(rightSpeed)+">"
    #print(s)
    ser.write(s.encode('utf-8'))

class robot:
    # TODO add all robot serial initializing functions to this 
    def __init__(self):
        self.motorLeftSpeed = 0
        self.motorRightSpeed = 0
        
        # 1 = detected, 0 = not detected
        self.leftID = 0
        self.rightID = 0
        
    def updateIDs(self, text):
        leftPos = text.find("LD: ")
        rightPos = text.find("RD: ")
        #print(text)
        
        #something peridocally messes up
        # not sure how to fix it so just dont do it if it doesnt work
        try:
            self.rightID = text[rightPos+4]
            self.leftID = text[leftPos+4]
            #print("Right sensor: " + self.rightID)
            #print("Left sensor: " + self.leftID)
        except IndexError:
            print("I dunno something messed up")
    def sendSpeed(self, leftSpeed, rightSpeed):
        s = "<L"+str(leftSpeed)+"R"+str(rightSpeed)+">"
        #print(s)
        ser.write(s.encode('utf-8'))

    
if __name__ == '__main__':
    ser = serial.Serial('/dev/ttyUSB0', 9600, timeout=1)
    ser.flush()
    arduinoRobot = robot()
    
    #let things initialize
    time.sleep(2)
    
    #start thread for constantly updating ID
    get_input_thread = threading.Thread(target=readFromSerial)
    get_input_thread.daemon = True
    get_input_thread.start()
    
    while True:
        #time.sleep(.02)
        # sendMotorCommand(5,6)
        # TODO: add threads for this?
        left = input("left motor: ")
        right = input("right motor: ")
        arduinoRobot.sendSpeed(left,right)
        
        #if ser.in_waiting > 0:
        #    readFromSerial()
            
            
