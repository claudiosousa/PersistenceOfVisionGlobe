#include <SPI.h>
#include "RF24.h"

RF24 radio(9, 10);

byte addresses[][6] = {
  "BoxPc", "PcBox"};

void setupRadio() {
  randomSeed(analogRead(0));
  radio.begin();

  radio.setPALevel(RF24_PA_MAX);

  radio.openWritingPipe(addresses[1]);
  radio.openReadingPipe(1, addresses[0]);
}

typedef struct RF24Message
{
  byte action;
  unsigned int length;
} 
RF24Message;

//RF24Message;

RF24Message message;
const byte messageSize = sizeof(message);

byte rfBuffer[bufferSize];

void sendRFData(byte* data, unsigned int dataLength){
  radio.stopListening();    

  radio.txStandBy();

  byte* dataPtr = data;
  unsigned int index = 0;
  while(index<dataLength){
    byte length2write = min(32, dataLength - index);  
    memcpy(&rfBuffer, dataPtr, length2write);
    dataPtr += length2write;  
    index+=length2write;
    while(!radio.writeFast(&rfBuffer, bufferSize)){       
      Serial.println("================ Fail: " + String(index));
      delay(20);      
    }
    radio.txStandBy();
  }
  Serial.println("Sended data");
}

void sendRFMessage(byte action, unsigned int dataLength){
  message.length = dataLength;
  message.action = action;
  //sendRFData(&message, messageSize));

  radio.stopListening();    

  if(!radio.write(&message, messageSize))
    Serial.println("================ Fail: " + String(action));
  radio.txStandBy();
  Serial.println("Sended msg");
}
/*
void sendImage(){
 radio.stopListening();    
 
 message.length = sizeof(imageArray);
 message.action = 168;
 while(!radio.write(&message, messageSize)){
 delay(20);
 }
 radio.txStandBy();
 
 byte* image = imageArray;
 unsigned c = 0;
 while(c<message.length){
 memcpy(&buffer, image, bufferSize);
 image += bufferSize;  
 c+=bufferSize;
 while(!radio.writeFast(&buffer, bufferSize)){       
 Serial.println("Fail: " + String(c));
 delay(20);      
 }
 radio.txStandBy();
 }
 Serial.println("Sended");
 }
 */






