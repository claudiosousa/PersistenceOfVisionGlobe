unsigned int outputPin = 3;
unsigned int sensorPin = 2;
volatile boolean inFront = false;
boolean ledON = false;

void setup(){
  pinMode(sensorPin, INPUT);
  pinMode(outputPin, OUTPUT);
  digitalWrite(outputPin, false);
  
  
   EICRA = _BV(ISC21);          //external interrupt on falling edge
   EIFR = _BV(INTF2);           //clear the interrupt flag (setting ISCnn can cause an interrupt)
   EIMSK = _BV(INT2);           //enable external interrupt


  //attachInterrupt(2, doCount, FALLING);
}

ISR(INT2_vect)
{
    static bool ledState;
    digitalWrite(outputPin, ledState = !ledState);
}

void loop() { 
}
/*
void loop() { 
  if (ledON!=inFront){
    ledON=inFront;
    digitalWrite(outputPin, ledON);   
  }
}

void doCount(){
   static bool ledState;
    digitalWrite(outputPin, ledState = !ledState);
}
*/
