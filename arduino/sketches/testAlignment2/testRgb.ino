void setupTestRgb() {
  //BGRBGRBG RBGRBGRB GRBGRBGR
  //00100100 10010010 01001001

}
void showColor(byte* color){
  writeToSrs(color);
  delay(1000);
}

void loopTestRgb() {
  showColor(t0);
  showColor(t1);
  showColor(t2);
    showColor(t3);
  showColor(t4);
  showColor(t5);
/*  showColor(red);
  showColor(green);
  showColor(blue);
  showColor(white);
  showColor(blank);   
*/  
}

