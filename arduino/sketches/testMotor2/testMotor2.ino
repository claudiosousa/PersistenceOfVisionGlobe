#include <Servo.h>

//Values:0-2000-700-900-1200
int value = 0; // set values you need to zero
int lastVal = -1;
Servo firstESC, secondESC; //Create as much as Servoobject you want. You can controll 2 or more Servos at the same time

void setup() {

  firstESC.attach(6);    // attached to pin 9 I just do this with 1 Servo
  Serial.begin(9600);    // start serial at 9600 baud

}

void loop() {

  //First connect your ESC WITHOUT Arming. Then Open Serial and follo Instructions
  if (lastVal!=value){
    lastVal = value;
    firstESC.writeMicroseconds(value);
    Serial.println(value, DEC);
  }
  if(Serial.available()) {
    value = Serial.parseInt();    // Parse an Integer from Serial

  }

}

