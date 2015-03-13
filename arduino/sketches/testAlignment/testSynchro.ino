#define SENSOR_PIN 2

const byte H_RES = 30;
volatile unsigned long nextFrameTime = 0;
volatile byte nextHIndex = 0;
volatile unsigned long horizontalStepDelta = 0;

byte hframes [][3] =   {
  { 0B00100100, 0B10010010, 0B01001001 }, //red
  { 0B01001001, 0B00100100, 0B10010010 },//green
  { 0B10010010, 0B01001001, 0B00100100 } //blue
};

void  setupTestSynchro() {
  pinMode(SENSOR_PIN, INPUT_PULLUP);
  attachInterrupt(INT0, turnDetected, FALLING);
  /*
    Serial.begin(9600);
    Serial.println(String(nextFrameTime));
  */
  nextFrameTime -= 1;
  //  Serial.println(String(nextFrameTime));
}

void loopTestSynchro() {
  if (micros() < nextFrameTime)
    return;
  nextFrameTime += horizontalStepDelta;
  showVFrame(nextHIndex);
  nextHIndex++;
}

void showVFrame(byte hIndex) {
  byte* hFramme = hframes[hIndex % 3];
  writeToSrs(hFramme);
}

volatile unsigned long lastTurnTime = 0;
void turnDetected() {
  unsigned long currentTurnTime = micros();
  unsigned long turnDuration = currentTurnTime - lastTurnTime;
  if (turnDuration < 10000)
    return;
//  Serial.println("New turn" + String(micros()));
  nextFrameTime = lastTurnTime =  currentTurnTime;
  horizontalStepDelta = turnDuration / H_RES;
  nextHIndex = 0;
}

