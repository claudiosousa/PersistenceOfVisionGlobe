#include <Servo.h>

//Values:0-2000-700-900-1200
int value = 0; // set values you need to zero
int lastVal = -1;
Servo firstESC; //Create as much as Servoobject you want. You can controll 2 or more Servos at the same time

void setup() {
  firstESC.attach(6);    // attached to pin 9 I just do this with 1 Servo
  firstESC.writeMicroseconds(0);
  delay(2000);
  firstESC.writeMicroseconds(700);
  delay(2000);
  firstESC.writeMicroseconds(900);
  delay(6000);
  firstESC.writeMicroseconds(1200);
}

void loop() {
}


