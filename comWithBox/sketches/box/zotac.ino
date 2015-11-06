#include <Servo.h>

byte POSITION_OFF = 20;
byte POSITION_ON = 60;
byte SERVO_PIN = 3;
byte PHOTO_PIN = A0;
int PHOTO_THRESHOLD = 512;
byte LED_PIN = 2;

Servo zotacServo; 

void setupZotac() {
  pinMode(LED_PIN, OUTPUT);
}

unsigned long lastLedCheck = 0;
void checkLEDStatus() {
  unsigned long time = millis();
  if (time- lastLedCheck<1000)
    return;
  lastLedCheck = time;
  digitalWrite(LED_PIN,analogRead(PHOTO_PIN) > PHOTO_THRESHOLD);
}

void pressZotacButton() {
  zotacServo.attach(SERVO_PIN);  // attaches the servo on pin 9 to the servo object
  zotacServo.write(POSITION_OFF); 
  delay(300);
  zotacServo.write(POSITION_ON);                  
  delay(350);
  zotacServo.write(POSITION_OFF);                  
  delay(300);
  zotacServo.detach();  // attaches the servo on pin 9 to the servo object
}



