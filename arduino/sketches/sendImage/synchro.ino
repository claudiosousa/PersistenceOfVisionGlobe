#define SENSOR_PIN 2

const byte ROTATION_SPEED = 80; //1 faster, 255 slower
const byte H_RES = 120;
volatile unsigned long nextFrameTime = 0;
volatile unsigned long horizontalStepDelta = 0;
volatile unsigned int  nextHIndex = 0;
volatile unsigned long turnDuration = 0;
volatile unsigned long lastTurnTime = 0;
volatile byte rotationOffset = 0;
volatile byte rotationOffsetCounter = 0;

void  setupSynchro() {

  pinMode(SENSOR_PIN, INPUT);

  EICRA = _BV(ISC21);          //external interrupt on falling edge
  EIFR = _BV(INTF2);           //clear the interrupt flag (setting ISCnn can cause an interrupt)
  EIMSK = _BV(INT2);           //enable external interrupt

  nextFrameTime = -1;
}
boolean ledsdWaitingForNextTurn = false;
void loopSynchro() {
  if (micros() < nextFrameTime)
    return;

  if (nextHIndex == H_RES) {
    if (!ledsdWaitingForNextTurn) {
      ledsdWaitingForNextTurn = true;
      writeToSrs(blankFrames, true);
    }
    return ;
  }
  rotationOffsetCounter++;    
  if (rotationOffsetCounter == ROTATION_SPEED){
    rotationOffset++;
    if (rotationOffset >H_RES) 
      rotationOffset = 0;
    rotationOffsetCounter = 0;
  }

  showVFrame(nextHIndex);
  nextHIndex++;
  nextFrameTime = lastTurnTime + (nextHIndex * turnDuration) / H_RES; 
  return ;
}

void showVFrame(unsigned int hIndex) {
  hIndex = (hIndex+rotationOffset)%H_RES;
  byte* hFramme = image+((hIndex %(H_RES/2))  * 24 * 2);
  writeToSrs(hFramme, hIndex>=(H_RES/2));
}

ISR(INT2_vect){
  unsigned long currentTurnTime = micros();
  turnDuration = currentTurnTime - lastTurnTime;
  if (turnDuration < 10000)
    return;
  //  Serial.println("New turn" + String(micros()));
  ledsdWaitingForNextTurn = false;
  nextFrameTime = lastTurnTime =  currentTurnTime;
  nextHIndex = 0;
}








