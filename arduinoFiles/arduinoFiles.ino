#include "motor.h"

// The Right Motors Enable Pin
// Labelled on the motor driver as ENA
const int motorRENPin = 10;
// The Right Motors IN1 Pin
// Labelled on the motor driver as IN1
const int motorRIN2Pin = 9;
// The Right Motors IN2 Pin
// Labelled on the motor driver as IN2
const int motorRIN1Pin = 8;

// The Left Motors Enable Pin
// Labelled on the motor driver as ENB
const int motorLENPin = 5;
// The Left Motors IN1 Pin
// Labelled on the motor driver as IN3
const int motorLIN2Pin = 7;
// The Left Motors IN2 Pin
// Labelled on the motor driver as IN4
const int motorLIN1Pin = 6;
Motor rightMotor(motorRIN1Pin, motorRIN2Pin, motorRENPin);
Motor leftMotor(motorLIN1Pin, motorLIN2Pin, motorLENPin);

const int rightIr = 3;
const int leftIr = 2;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(rightIr, INPUT);
  pinMode(leftIr, INPUT);
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {

  int objectLeft = digitalRead(leftIr);
  int objectRight = digitalRead(rightIr);
  if(objectRight == 0 && objectLeft == 0) {
    Serial.print("Turning around"); 
    rightMotor.forward(130);
    leftMotor.backward(130);
  }
  else if(objectLeft == 0){
    Serial.print("turning away-ob on left "); 
    leftMotor.forward(130);
    rightMotor.freeRun();
  }
  
  else if(objectRight == 0){
    Serial.print("turning away-ob on right ");
    leftMotor.freeRun();
    rightMotor.forward(130); 
  }
  else{
    rightMotor.forward(130);
    leftMotor.forward(130);
    Serial.print("nothing detected");
  }
  Serial.println();
}
