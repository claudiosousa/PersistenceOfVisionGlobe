#ifndef cbi
#define cbi(sfr, bit) (_SFR_BYTE(sfr) &= ~_BV(bit))
#endif
#ifndef sbi
#define sbi(sfr, bit) (_SFR_BYTE(sfr) |= _BV(bit))
#endif

#define SR_PORT PORTB
#define SR_LATCH 4
#define SR_CLOCK 3
#define SR_DATA 2

byte SrsCount = 3;
void setupSrs(){
  DDRB = (1<<SR_LATCH) | (1<<SR_CLOCK) | (1<<SR_DATA);
}
void writeToSrs(byte* outputbuffer) {

  cbi(SR_PORT, SR_LATCH);

  for (int i = SrsCount - 1; i >= 0 ; i--) {
    for  (int j = 0; j < 8; j++) {
      byte outputByte = outputbuffer[i];
      cbi(SR_PORT, SR_CLOCK);
      if (outputByte & (1 << j))
        sbi(SR_PORT, SR_DATA);
      else
        cbi(SR_PORT, SR_DATA);

      sbi(SR_PORT, SR_CLOCK);
    }
  }

  sbi(SR_PORT, SR_LATCH);
}


