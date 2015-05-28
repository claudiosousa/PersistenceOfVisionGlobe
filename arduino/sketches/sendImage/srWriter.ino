#ifndef cbi
#define cbi(sfr, bit) (_SFR_BYTE(sfr) &= ~_BV(bit))
#endif
#ifndef sbi
#define sbi(sfr, bit) (_SFR_BYTE(sfr) |= _BV(bit))
#endif

#define SR_PORT PORTC
#define SR_LATCH 6
#define SR_CLOCK 7

byte SrsCount = 3;
void setupSrs(){
  DDRC = (1<<SR_LATCH) | (1<<SR_CLOCK);
  DDRA = B11111111; 
  DDRD = B11111111;
}

void writeToSrs(byte* outputbuffer, boolean reverse) {

  cbi(SR_PORT, SR_LATCH);

  for (int i = 24-1; i >= 0 ; i--) {
    cbi(SR_PORT, SR_CLOCK);

    if (reverse){
      PORTA =  outputbuffer[i];
      PORTD =  outputbuffer[i+24];
    }
    else{
      PORTD =  outputbuffer[i];
      PORTA =  outputbuffer[i+24];
    }
    sbi(SR_PORT, SR_CLOCK);
  }
  sbi(SR_PORT, SR_LATCH);
}




