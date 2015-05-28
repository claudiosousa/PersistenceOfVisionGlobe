#define SENSOR_PIN 2

const byte H_RES = 90;
volatile unsigned long nextFrameTime = 0;
volatile unsigned long horizontalStepDelta = 0;
volatile unsigned int  nextHIndex = 0;
volatile bool ledsdWaitingForNextTurn = true;

//byte hframes[7][3] ;
byte* hframes = (byte*)malloc(24);

void fillArray(byte* color){
  memcpy(hframes, color, 3);
  hframes+=3;
}
void  setupTestSynchro() {
  fillArray(red);
  fillArray(green);
  fillArray(blue);
  
  fillArray(yellow);
  fillArray(purple);
  fillArray(cyan);
  fillArray(white);
  fillArray(blank);

  hframes-=24;                                   

  pinMode(SENSOR_PIN, INPUT);


  EICRA = _BV(ISC21);          //external interrupt on falling edge
  EIFR = _BV(INTF2);           //clear the interrupt flag (setting ISCnn can cause an interrupt)
  EIMSK = _BV(INT2);           //enable external interrupt

  nextFrameTime -= 1;
  //  Serial.println(String(nextFrameTime));
}

void loopTestSynchro() {
  if (micros() < nextFrameTime)
    return;

  if (nextHIndex == H_RES) {
    /*if (!ledsdWaitingForNextTurn) {
      ledsdWaitingForNextTurn = true;
      writeToSrs(blank);
    }*/
    return;
  }
  nextFrameTime += horizontalStepDelta;
  showVFrame(nextHIndex);
  nextHIndex++;
}

void showVFrame(unsigned int hIndex) {
  byte* hFramme = hframes+(hIndex % 3)*3;
  writeToSrs(hFramme);
}

volatile unsigned long lastTurnTime = 0;
ISR(INT2_vect){
  unsigned long currentTurnTime = micros();
  unsigned long turnDuration = currentTurnTime - lastTurnTime;
  if (turnDuration < 10000)
    return;
  //  Serial.println("New turn" + String(micros()));
  nextFrameTime = lastTurnTime =  currentTurnTime;
  horizontalStepDelta = turnDuration / H_RES;
  nextHIndex = 0;
  ledsdWaitingForNextTurn = false;
}





