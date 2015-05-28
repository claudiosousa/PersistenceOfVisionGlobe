void setupTestRgb() {
  //BGRBGRBG RBGRBGRB GRBGRBGR
  //00100100 10010010 01001001

}
void showColor(byte* color){
  writeToSrs(color);
  delay(3000);
}

void loopTestRgb() {
  showColor(red);
  showColor(green);
  showColor(blue);
  showColor(purple);
  showColor(yellow);
  showColor(cyan);
  showColor(white);
  showColor(blank);               

}

