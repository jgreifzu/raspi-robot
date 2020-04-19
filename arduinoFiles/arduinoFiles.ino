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

const byte numChars = 10;
char receivedChars[numChars];

int leftMotorSpeed = 0;
int rightMotorSpeed = 0;

boolean newData = false;

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
  Serial.print("\nLD: ");
  Serial.print(objectLeft);
  Serial.print(" RD: ");
  Serial.print(objectRight);
  

  
//  if(objectRight == 0 && objectLeft == 0) {
//    //Serial.print("Turning around");
//    rightMotorSpeed = 130;
//    leftMotorSpeed = -130; 
//    //rightMotor.forward(130);
//    //leftMotor.backward(130);
//  }
//  else if(objectLeft == 0){
//    //Serial.print("turning away-ob on left ");
//    rightMotorSpeed = 0;
//    leftMotorSpeed = 130;  
//    //leftMotor.forward(130);
//    //rightMotor.freeRun();
//  }
//  
//  else if(objectRight == 0){
//    //Serial.print("turning away-ob on right ");
//    rightMotorSpeed = 130;
//    leftMotorSpeed = 0;  
//    //leftMotor.freeRun();
//    //rightMotor.forward(130); 
//  }
//  else{
//    rightMotorSpeed = 130;
//    leftMotorSpeed = 130;  
//    //Serial.print("nothing detected");
//  }
  
//  Serial.print("R: ");
//  Serial.print(rightMotorSpeed, DEC);
//  Serial.print(",L: ");
//  Serial.print(leftMotorSpeed, DEC);
//  
//  Serial.print(", LD: ");
//  Serial.print(objectLeft, DEC);
//  Serial.print(", RD: ");
//  Serial.print(objectRight, DEC);

//  if(rightMotorSpeed > 0){
//    rightMotor.forward(rightMotorSpeed);
//  }
//  if(rightMotorSpeed == 0){
//    rightMotor.freeRun();
//  }
//  if(rightMotorSpeed < 0){
//    rightMotor.backward(rightMotorSpeed);
//  }
//
//  if(leftMotorSpeed > 0){
//    leftMotor.forward(leftMotorSpeed);
//  }
//  if(leftMotorSpeed == 0){
//    leftMotor.freeRun();
//  }
//  if(leftMotorSpeed < 0){
//    leftMotor.backward(leftMotorSpeed);
//  }
  
  
  //Serial.println();
  recvWithStartEndMarkers();
  showNewData();
  
}
void recvWithStartEndMarkers() {
    static boolean recvInProgress = false;
    static byte ndx = 0;
    char startMarker = '<';
    char endMarker = '>';
    char rc;
    while (Serial.available() > 0 && newData == false) {
        rc = Serial.read();

        if (recvInProgress == true) {
            if (rc != endMarker) {
                receivedChars[ndx] = rc;
                ndx++;
                if (ndx >= numChars) {
                    ndx = numChars - 1;
                }
            }
            else {
                receivedChars[ndx] = '\0'; // terminate the string
                recvInProgress = false;
                ndx = 0;
                newData = true;
            }
        }

        else if (rc == startMarker) {
            recvInProgress = true;
        }
    }
}

void showNewData() {
    if (newData == true) {
        
        String left = String(receivedChars[1]);
        String right = String(receivedChars[3]);
        //int leftInt = left[0].toInt()*10 + left[1];
        int valueLeft = String(receivedChars[1]).toInt();
        int valueRight = String(receivedChars[3]).toInt();
//        Serial.print("Left: ");
//        Serial.print(valueLeft*50);
//        Serial.print(" Right: ");
//        Serial.println(valueRight*50);

        // apply serial motor values
        // only use 1-5 for foward
        if(valueLeft < 5){
          leftMotor.forward(valueLeft * 50);
          Serial.print("Left: ");
          Serial.print(valueLeft*50);
        }
        // go backwards if 6-10
        else if(valueLeft > 5 && valueLeft <10) {
          leftMotor.backward((valueLeft - 5)*50);
          Serial.print("Back Left: ");
          Serial.print((valueLeft-5)*50);
        }

        if(valueRight < 5){
          rightMotor.forward(valueRight * 50);
          Serial.print("Right: ");
          Serial.print(valueRight*50);
        }
        else if(valueRight > 5 && valueRight <10) {
          rightMotor.backward((valueRight - 5)*50);
          Serial.print("Back Rigth: ");
          Serial.print((valueRight-5)*50);
        }

        newData = false;
    }
}
