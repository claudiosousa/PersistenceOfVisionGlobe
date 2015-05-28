#include <Servo.h>

// usually the rotary encoders three pins have the ground pin in the middle
enum PinAssignments {
  dtPin = 2,   // right (labeled DT on our decoder, yellow wire)
  clkPin = 3,   // left (labeled CLK on our decoder, green wire)
  swPin = 4,    // switch (labeled SW on our decoder, orange wire)
  motorDataPin = 9,
  motorVccPin = 13
};

volatile unsigned int encoderMin = 53;
volatile unsigned int encoderMax = 180;
Servo myservo;

volatile unsigned int encoderPos = 53;  // a counter for the dial
unsigned int lastReportedPos = 1;   // change management
static boolean rotating = false;      // debounce management

// interrupt service routine vars
boolean A_set = false;              
boolean B_set = false;


void setup() {
  TCCR1B = TCCR1B & 0b11111000 | 0x02;
  pinMode(dtPin, INPUT_PULLUP); // new method of enabling pullups
  pinMode(clkPin, INPUT_PULLUP); 
  pinMode(swPin, INPUT_PULLUP);
  //pinMode(motorVccPin, OUTPUT);

  //digitalWrite(motorVccPin, HIGH);

  // encoder pin on interrupt 0 (pin 2)
  attachInterrupt(0, doEncoderA, CHANGE);
  // encoder pin on interrupt 1 (pin 3)
  attachInterrupt(1, doEncoderB, CHANGE);
  myservo.attach(motorDataPin);
  myservo.write(0);

  Serial.begin(9600);  // output
/*
 Serial.println("Now writing maximum output.");
  Serial.println("Turn on power source, then wait 2 seconds and press any key.");
  myservo.writeMicroseconds(2000);

  // Wait for input
  while (!Serial.available());
  Serial.read();

  // Send min output
  Serial.println("Sending minimum output");
  myservo.writeMicroseconds(1200);
*/
}

// main loop, work is done by interrupt service routines, this one only prints stuff
void loop() { 
  rotating = true;  // reset the debouncer

  if (lastReportedPos != encoderPos) {
    unsigned int encoderVal2use = (encoderPos == 53?0:(encoderPos == 54?10:encoderPos));
    Serial.println(encoderVal2use, DEC);
    lastReportedPos = encoderPos;
    myservo.write(encoderVal2use);
  }
  if (digitalRead(swPin) == LOW )  {
    encoderPos = encoderMin;
  }
}

// Interrupt on A changing state
void doEncoderA(){
  // debounce
  if ( rotating ) delay (1);  // wait a little until the bouncing is done

  // Test transition, did things really change? 
  if( digitalRead(dtPin) != A_set ) {  // debounce once more
    A_set = !A_set;

    // adjust counter + if A leads B
    if ( A_set && !B_set && encoderPos > encoderMin) 
      encoderPos -= 1;

    rotating = false;  // no more debouncing until loop() hits again
  }
}

// Interrupt on B changing state, same as A above
void doEncoderB(){
  if ( rotating ) delay (1);
  if( digitalRead(clkPin) != B_set ) {
    B_set = !B_set;
    //  adjust counter - 1 if B leads A
    if( B_set && !A_set && encoderPos < encoderMax) 
      encoderPos += 1;

    rotating = false;
  }
}





