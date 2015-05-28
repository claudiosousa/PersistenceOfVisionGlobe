//  GBRGBRGB    RGBRGBRG    BRGBRGBR
//  10001000    11000101    01100010
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
