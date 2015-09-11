byte SPIN_RELAY_PIN = 4;

void setupSpin(){
  pinMode(SPIN_RELAY_PIN, OUTPUT);
  spinPowerOff();
}
void spinPowerOff(){
  digitalWrite(SPIN_RELAY_PIN, 0);
}
void spinPowerOn(){
  digitalWrite(SPIN_RELAY_PIN, 1);
}

