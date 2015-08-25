#include <SPI.h>
#include "RF24.h"

const int datalength =  1540;
byte data[datalength];
RF24 radio(9, 10);
byte addresses[][6] = {"BoxPc", "PcBox"};
void setupRF24() {
  radio.begin();
  
 radio.setPALevel(RF24_PA_MAX);
  radio.setDataRate(RF24_1MBPS);
  radio.setAutoAck(1);                     // Ensure autoACK is enabled
  radio.setRetries(2,15);                  // Optionally, increase the delay between retries & # of retries
  
  radio.setCRCLength(RF24_CRC_8);  

  radio.openWritingPipe(addresses[0]);
  radio.openReadingPipe(1, addresses[1]);

  radio.startListening();
}

void tryReadRF24() {

  if ( radio.available()) {
    // Variable for the received timestamp
    byte payload;
    while (radio.available()) {                                   // While there is data ready
      radio.read( &payload, 1 );             // Get the payload
    }

    radio.stopListening();  
    // First, stop listening so we can talk
    radio.write( &payload, 1);              // Send the final one back.

    radio.startListening();    
  }
}



