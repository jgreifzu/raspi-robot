from flask import Flask, render_template
import serialComm
import serial
from time import sleep
arduinoRobot = None
app = Flask(__name__)
#run by doing flask run --host=0.0.0.0

@app.route('/')
def index():
  
  return render_template('index.html')

@app.route('/go_foward/')
def drive_robot_foward():
  print ('driving robot foward')
  arduinoRobot.sendSpeed(3,3)
  return render_template('index.html')
@app.route('/go_right/')
def drive_robot_right():
  print ('driving robot right')
  return render_template('index.html')
@app.route('/go_left/')
def drive_robot_left():
  print ('driving robot left')
  return render_template('index.html')
@app.route('/go_back/')
def drive_robot_backward():
  print ('driving robot backward')
  return render_template('index.html')

if __name__ == '__main__':
  ser = serial.Serial('/dev/ttyUSB0', 9600, timeout=1)
  ser.flush()
  arduinoRobot = serialComm.robot()
  sleep(2)
  app.run(debug=True)