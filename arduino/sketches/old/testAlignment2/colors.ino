//  GBRGBRGB    RGBRGBRG    BRGBRGBR
//  10001000    11000101    01100010
//  RBGRBGRG    BRBGRGBR    GBRGBRGB
//  10001000    01001001    00100100
byte t0[3] = {
  0B10000010, 0B00001000, 0B00100000};
byte t1[3] = {
  0B01000001, 0B00000100, 0B00010000};
byte t2[3] = {
  0B00100000, 0B10000010, 0B00001000};
byte t3[3] = {
  0B00010000, 0B01000001, 0B00000100};
byte t4[3] = {
  0B00001000, 0B00100000, 0B10000010};
byte t5[3] = {
  0B00000100, 0B00010000, 0B01000001};
byte green[3] = {
  0B01001001, 0B00100100, 0B10010010};
byte blue[3] = {
  0B00100100, 0B10010010, 0B01001001};
byte red[3] = {
  0B10010010, 0B01001001, 0B00100100};
byte yellow[3];
byte purple[3]; 
byte cyan[3];
byte white[3] = {
  0B11111111,0B11111111,0B11111111};
byte blank[3] = {
  0,0,0};
  
  
void mixColors(byte* input1, byte* input2, byte* output){
  for (int i = 0; i <3 ; i++) {
    output[i] = input1[i] | input2[i];
  }
}


void setupColors(){
  mixColors(red, green, yellow);
  mixColors(red, blue, purple);
  mixColors(green, blue, cyan);
}
