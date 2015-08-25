#include <SPI.h>
#include "RF24.h"

RF24 radio(1, 0);
byte addresses[][6] = {
  "BoxPc", "PcBox"};


typedef struct RF24Message
{
  byte action;
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

unsigned int messageReceivedAt;
void reset() {
  message.action = 0;
  received = 0; 
}

void tryReadRF24() {  

  if (!radio.available()){
    return;
  }
  if ( millis()-messageReceivedAt>3000)
    reset();
  if (message.action == 0){
    while(radio.available()){
      radio.read(&message, messageSize);
    }
    messageReceivedAt =  millis();
  }

  byte* b;
  boolean finishedMessage = false;
  switch (message.action){
  case 167:
    radio.read(&buffer, 1);
    ROTATION_SPEED = buffer[0];
    break;
  case 168:

    while(radio.available() && !finishedMessage){ 
      byte toRead = min(32, message.length - received);
      radio.read(&buffer, toRead);
      b = imageArray + received;
      memcpy(b, buffer, toRead);
      received += toRead;
      if (received >= message.length){
        reset();  
        finishedMessage = true;        
      }  
    }

    break;  
  default:
    reset();  
  }  
}




















