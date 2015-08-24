#include <Servo.h>

Servo firstESC;
void setupMotor(){
  pinMode(13, OUTPUT);
  firstESC.attach(6);
  firstESC.writeMicroseconds(0);
  delay(100);
  firstESC.writeMicroseconds(700);
}

void stopMotor(){
  firstESC.writeMicroseconds(700);
//  digitalWrite(13, 0);
}


void startMotor(){
  firstESC.writeMicroseconds(900);
  delay(2000);
  firstESC.writeMicroseconds(1200);
  //  digitalWrite(13, 1);
}

