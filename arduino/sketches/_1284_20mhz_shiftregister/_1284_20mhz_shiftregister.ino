
void setup() {
  setupSrs();
}

void loop() {
  //GBR GBR GB  R GBR GBR G  BR GBR GBR
  //100 010 00  1 100 010 1  01 100 010
  byte colors[] = {    
    0B10001000,0B11000101,0B01100010    };
  writeToSrs(colors  );
  /*
  for  (int j = 0; j < 360; j++) {
   writeToSr(0B10010010);
   }
   for  (int j = 0; j < 360; j++) {
   writeToSr(0B01001001);
   }
   for  (int j = 0; j < 360; j++) {
   writeToSr(0B00100100);
   }
   */
}




