void setup() {
  setupSpin();
  setupZotac();

  delay(1000);  
  pressZotacButton();

  setupRadio();
  setupPcMessaging();
  setupMotor();
}

void loop() {
  tryReadPCMessage();
  checkLEDStatus();
}












