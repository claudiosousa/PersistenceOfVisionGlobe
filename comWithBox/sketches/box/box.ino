void setup() {
  setupSpin();

  delay(1000);  
  pressZotacButton();

  setupRadio();
  setupPcMessaging();
  setupMotor();
}


void loop() {
  tryReadPCMessage();
}












