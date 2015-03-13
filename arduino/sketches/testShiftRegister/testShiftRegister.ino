//Pin connected to ST_CP of 74HC595
int latchPin = 12;
//Pin connected to SH_CP of 74HC595
int clockPin = 11;
////Pin connected to DS of 74HC595
int dataPin = 10;

void setup() {
  //set pins to output because they are addressed in the main loop
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  
}

void loop() {
    //digitalWrite(latchPin, true);
    //delay(1000);
    //digitalWrite(latchPin, false  );
    //delay(1000);
    //return;
  //count up routine
  for (int j = 0; j < 256; j++) {
    //ground latchPin and hold low for as long as you are transmitting
    digitalWrite(latchPin, LOW);
    shiftOut(dataPin, clockPin, LSBFIRST, j);   
    //return the latch pin high to signal chip that it 
    //no longer needs to listen for information
    digitalWrite(latchPin, HIGH);
    //digitalWrite(latchPin, LOW);
    delay(100);
  }
} 
