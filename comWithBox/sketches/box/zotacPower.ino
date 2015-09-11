#include <Servo.h>

byte POSITION_OFF = 50;
byte POSITION_ON = 60;
byte SERVO_PIN = 3;

Servo zotacServo; 


void pressZotacButton() {
  zotacServo.attach(SERVO_PIN);  // attaches the servo on pin 9 to the servo object
  zotacServo.write(POSITION_OFF); 
  delay(200);
  zotacServo.write(POSITION_ON);                  
  delay(250);
  zotacServo.write(POSITION_OFF);                  
  delay(200);
  zotacServo.detach();  // attaches the servo on pin 9 to the servo object
}

