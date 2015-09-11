#include <Servo.h>
//0-2000-700-900-1200
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
}
void setMotorSpeed(int speed){
   firstESC.writeMicroseconds(min(1600, speed));
}

void startMotor(){
  firstESC.writeMicroseconds(1300);
  delay(2000);
  firstESC.writeMicroseconds(1400);
}

