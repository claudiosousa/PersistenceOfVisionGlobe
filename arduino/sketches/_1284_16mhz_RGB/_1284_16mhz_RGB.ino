unsigned int latchPin = 22;
unsigned int clockPin = 23;
unsigned int ledPin = 3;

void setup() {
  //set pins to output because they are addressed in the main loop
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(ledPin, OUTPUT);
  DDRA = B11111111; 
  DDRD = B11111111; 
  PORTA = 0;  
}
//GBR GBR GB  R GBR GBR G  BR GBR GBR
//100 010 00  1 100 010 1  01 100 010
byte green[] = {
  0B01001001, 0B00100100, 0B10010010};
byte blue[] = {
  0B00100100, 0B10010010, 0B01001001};
byte red[] = {
  0B10010010, 0B01001001, 0B00100100};


byte white[] = {
  0B11111111,0B11111111,0B11111111};
byte blank[] = {
  0,0,0};
byte test[] = {  
  0B00100100, 0B10010010, 0B01001001};
void loop() {
  write2shiftregisters(red);
  delay(2000);
  write2shiftregisters(green);
  delay(2000);
  write2shiftregisters(blue);
  delay(2000);
  write2shiftregisters(mixColors(red, green));
  delay(2000);
  write2shiftregisters(mixColors(red, blue));
  delay(2000);
  write2shiftregisters(mixColors(green, blue));
  delay(2000);
  write2shiftregisters(white);
  delay(2000);
  write2shiftregisters(blank);
  delay(2000);
  /*
  write2shiftregisters(green);
   delay(3000);
   write2shiftregisters(blue);
   delay(3000);
   */
} 

byte* mixColors(byte* input1, byte* input2){
  byte result[3];
  for (int i = 0; i <3 ; i++) {
    result[i] = input1[i] | input2[i];
  }
  return result;
}

void write2shiftregisters(byte* outputbuffer){
  digitalWrite(ledPin,  !digitalRead(ledPin));
  digitalWrite(latchPin, LOW);
  for (int i = 3-1; i >= 0 ; i--) {
    byte outputByte = outputbuffer[i];
    for  (int j = 0; j <= 7; j++) {
      digitalWrite(clockPin, LOW);
      PORTA = PORTD = (outputByte & (1 << j))?255:0;
      digitalWrite(clockPin, HIGH);
    }
  }
  digitalWrite(latchPin, HIGH);
}



