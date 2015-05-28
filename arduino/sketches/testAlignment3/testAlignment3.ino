#define OUTPUT_PIN 3

void setup() {  
  pinMode(3, OUTPUT);
  for(int i = 0;i<8;i++){
    digitalWrite(3, true);
    delay(100);
    digitalWrite(3, false);
    delay(100);
  }
  setupSrs();
  setupColors();
  setupTestSynchro();

}

void loop() {  
  //loopTestSynchro();

  loopTestRgb();
}






