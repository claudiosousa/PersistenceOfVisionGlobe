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

void writeToSrs(byte* outputbuffer) {

  cbi(SR_PORT, SR_LATCH);

  for (int i = 3-1; i >= 0 ; i--) {
    byte outputByte = outputbuffer[i];
    for  (int j = 0; j <= 7; j++) {
      cbi(SR_PORT, SR_CLOCK);

      PORTD =   PORTA = (outputByte & (1 << j))?255:0;

      sbi(SR_PORT, SR_CLOCK);
    }
  }

  sbi(SR_PORT, SR_LATCH);
}



