#include <Servo.h>

byte POSITION_OFF = 50;
byte POSITION_ON = 60;
byte SERVO_PIN = 3;
byte PHOTO_PIN = A0;
byte PHOTO_THRESHOLD = 200;
byte LED_PIN = 0;

Servo zotacServo; 

void setupZotac() {
  pinMode(LED_PIN);
}

unsigned long lastLedCheck = 0;
void checkLEDStatus() {
  long unsigned time = millis();
  if (time- lastLedCheck<1000)
    return;
  lastLedCheck = time;
  digitalWrite(LED_PIN, analogRead(PHOTO_PIN) > PHOTO_THRESHOLD);
}

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



