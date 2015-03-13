
void setup() {
  setupSrs();

  //BGRBGRBG RBGRBGRB GRBGRBGR
  //00100100 10010010 010010010

  for (int i = 0; i < 3; i++) {
    //RRR
    byte red[] = { 0B00100100, 0B10010010, 0B010010010 };
    writeToSrs(red);
    delay(1000);
    //GGG
    byte green[] = { 0B01001001, 0B00100100, 0B10010010 };
    writeToSrs(green);
    delay(1000);
    //BBB
    byte blue[] = { 0B10010010, 0B01001001, 0B00100100 };
    writeToSrs(blue);
    delay(1000);
  }
}

void loop() {
 //BGRBGRBG RBGRBGRB GRBGRBGR
 //00101010 00010101 00001010

  byte rgb[] = { 0B00101010, 0B00010101, 0B00001010};
  writeToSrs(rgb);
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




