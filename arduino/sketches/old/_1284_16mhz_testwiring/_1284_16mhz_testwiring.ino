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
  digitalWrite(ledPin, HIGH);
}

void loop() {
  for (int j = 0; j < 256; j++) {
    digitalWrite(latchPin, LOW);
    PORTA = PORTD = j;
    digitalWrite(clockPin, HIGH);
    digitalWrite(clockPin, LOW);
    digitalWrite(latchPin, HIGH);
    delay(500);
  }
} 
