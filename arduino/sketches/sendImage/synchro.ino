#define SENSOR_PIN 2

const byte H_RES = 120;
volatile unsigned long nextFrameTime = 0;
volatile unsigned long horizontalStepDelta = 0;
volatile unsigned int  nextHIndex = 0;
volatile unsigned long turnDuration = 0;
volatile unsigned long lastTurnTime = 0;

void  setupSynchro() {

  pinMode(SENSOR_PIN, INPUT);

  EICRA = _BV(ISC21);          //external interrupt on falling edge
  EIFR = _BV(INTF2);           //clear the interrupt flag (setting ISCnn can cause an interrupt)
  EIMSK = _BV(INT2);           //enable external interrupt

  nextFrameTime = -1;
}

void loopSynchro() {
  if (micros() < nextFrameTime)
    return false;

  if (nextHIndex == H_RES) {
    /*if (!ledsdWaitingForNextTurn) {
     ledsdWaitingForNextTurn = true;
     writeToSrs(blank);
     }*/
    return false;
  }
  showVFrame(nextHIndex);
  nextHIndex++;
  nextFrameTime = lastTurnTime + (nextHIndex * turnDuration) / H_RES; 
  return true;
}

void showVFrame(unsigned int hIndex) {
    byte* hFramme = image+((hIndex %(H_RES/2))  * 24 * 2);
    writeToSrs(hFramme, hIndex>=(H_RES/2));
}

ISR(INT2_vect){
  unsigned long currentTurnTime = micros();
  turnDuration = currentTurnTime - lastTurnTime;
  if (turnDuration < 10000)
    return;
  //  Serial.println("New turn" + String(micros()));
  nextFrameTime = lastTurnTime =  currentTurnTime;
  nextHIndex = 0;
}







