#include <SPI.h>
#include "RF24.h"

RF24 radio(1, 0);
byte addresses[][6] = {
  "BoxPc", "PcBox"};

typedef struct RF24Message
{
  unsigned int action;
  unsigned int length;
} 
RF24Message;

RF24Message message;
const byte messageSize = sizeof(message);

const byte bufferSize = 32;
byte buffer[bufferSize];
unsigned int received = 0;

void setupRF24() {
  radio.begin();

  radio.setPALevel(RF24_PA_MAX);
  //  radio.setDataRate(RF24_250KBPS);
  //  radio.setAutoAck(1);                     // Ensure autoACK is enabled
  radio.setRetries(15,15);                  // Optionally, increase the delay between retries & # of retries

  radio.openWritingPipe(addresses[0]);
  radio.openReadingPipe(1, addresses[1]);

  radio.startListening();
  reset();        
}

void reset() {
  memset(&message,0, messageSize);
  received = 0; 
}

void readRF24() {  
  byte* b;

  if (!radio.available()){
    return;
  }

  if (message.action == 0){
    while(radio.available()){       
      radio.read(&message, messageSize);
    }    
  }

  switch (message.action){
  case 1684:
    while(radio.available()){       
      radio.read(&buffer, bufferSize);
      b = imageArray + received;
      memcpy(b, buffer, bufferSize);
      received += bufferSize;
      if (received >= message.length){
        reset();        
        break;        
      }  
    }

    //memset(&imageArray, 0, sizeof(imageArray));
    //memcpy(b, &count, messageSize);
    break;  

  default:
    // Perdu, try again
    reset();        
    break;
  }
}











