
/*
* Getting Started example sketch for nRF24L01+ radios
* This is a very basic example of how to send data from one node to another
* Updated: Dec 2014 by TMRh20
*/

#include <SPI.h>
#include "RF24.h"


/****************** User Config ***************************/
/***      Set this radio as radio number 0 or 1         ***/
// Used to control whether this node is sending or receiving (0: receive, 1:send)
#define arduino328sender true    

#if arduino328sender
  RF24 radio(9, 10);
  bool role = 1;
#else
  RF24 radio(9, 10);
  bool role = 0;
#endif

 
bool radioNumber = role;

/* Hardware configuration: Set up nRF24L01 radio on SPI bus plus pins 7 & 8 */
/**********************************************************/

byte addresses[][6] = {"BoxPc", "PcBox"};
const int datalength =  1540;
byte data[datalength];

void setup() {
   randomSeed(analogRead(0));              //Seed for random number generation
  pinMode(13, OUTPUT);
  for(int i=0; i<datalength; i++){
     data[i] = random(255);        
  }
  Serial.begin(57600);
  Serial.println(F("RF24/examples/GettingStarted"));
  Serial.println(F("*** PRESS 'T' to begin transmitting to the other node"));

  radio.begin();

  // Set the PA Level low to prevent power supply related issues since this is a
  // getting_started sketch, and the likelihood of close proximity of the devices. RF24_PA_MAX is default.
  //radio.setPALevel(RF24_PA_LOW);

  radio.setPALevel(RF24_PA_MAX);
//  radio.setDataRate(RF24_250KBPS);
//  radio.setAutoAck(1);                     // Ensure autoACK is enabled
  //radio.setRetries(15,15);                  // Optionally, increase the delay between retries & # of retries
  
  //radio.setCRCLength(RF24_CRC_8);  


  // Open a writing and reading pipe on each radio, with opposite addresses
  if (radioNumber) {
    radio.openWritingPipe(addresses[1]);
    radio.openReadingPipe(1, addresses[0]);
  } else {
    radio.openWritingPipe(addresses[0]);
    radio.openReadingPipe(1, addresses[1]);
  }

  // Start the radio listening for data
  radio.startListening();
}

byte tosend = 0;
void loop() {


  /****************** Ping Out Role ***************************/
  if (role == 1)  {

    radio.stopListening();                                    // First, stop listening so we can talk.


    Serial.println(F("Now sending"));

    unsigned long sent_time = micros();                             // Take the time, and send it.  This will block until complete
    if (!radio.write(&data, datalength)) {
      Serial.println(F("failed"));
    }else
      Serial.println(F("No failed!"));
/*
    radio.startListening();                                    // Now, continue listening
    unsigned long started_waiting_at = micros();               // Set up a timeout period, get the current microseconds
    boolean timeout = false;                                   // Set up a variable to indicate if a response was received or not

    while ( ! radio.available() ) {                            // While nothing is received
      if (micros() - started_waiting_at > 200000 ) {           // If waited longer than 200ms, indicate timeout and exit while loop
        timeout = true;
        break;
      }
    }

    if ( timeout ) {                                            // Describe the results
      Serial.println(F("Failed, response timed out."));
    } else {
      */
      byte res;
      radio.read( &res, 1 );
      unsigned long time = micros();

      // Spew it
      Serial.print(F("Sent "));
      Serial.print(tosend);
      Serial.print(F(", Got response "));
      Serial.print(res);
      Serial.print(F(", Round-trip delay "));
      Serial.print(time - sent_time);
      Serial.println(F(" microseconds"));
      /*
    }

    // Try again 1s later
    //delay(1000);
    */
  }



  /****************** Pong Back Role ***************************/

  if ( role == 0 )
  {
    unsigned long got_time = micros();
 
    if ( radio.available()) {
      // Variable for the received timestamp
      while (radio.available()) {                                   // While there is data ready
        radio.read( &data, 1 );             // Get the payload
      }

      radio.stopListening();  
      // First, stop listening so we can talk
      radio.write( &data[0], 1);              // Send the final one back.
      radio.startListening();    
      Serial.print(F("Received "));
      Serial.println(data[0]);
// Now, resume listening so we catch the next packets.
 //     Serial.print(F("Sent response "));
//      Serial.println(got_time);
    }
    //Serial.println(micros()-got_time);
  }




  /****************** Change Roles via Serial Commands ***************************/

  if ( Serial.available() )
  {
    char c = toupper(Serial.read());
    if ( c == 'T' && role == 0 ) {
      Serial.println(F("*** CHANGING TO TRANSMIT ROLE -- PRESS 'R' TO SWITCH BACK"));
      role = 1;                  // Become the primary transmitter (ping out)

    } else if ( c == 'R' && role == 1 ) {
      Serial.println(F("*** CHANGING TO RECEIVE ROLE -- PRESS 'T' TO SWITCH BACK"));
      role = 0;                // Become the primary receiver (pong back)
      radio.startListening();
    }
  }

} // Loop

