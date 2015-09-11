void setupPcMessaging(){
  Serial.begin(115200);
  Serial.println("Arduino started...");
}

enum  messageReadState{  
  readAction,
  readBodyLength,
  readbody
};

struct messageType{  
  byte action;
  unsigned int bodyLength;
};

const byte bufferSize = 32;
byte pcBuffer[32];
byte pcBufferReadLength = 0;

unsigned int readBodyIndex = 0;
messageReadState readState = readAction;
messageType currentMessage;
byte inByte;

void tryReadPCMessage(){
  while (Serial.available()) {    
    switch(readState)  {
    case readAction:
      inByte = Serial.read();
      currentMessage.action = inByte;
      readState = readBodyLength;
      break;
    case readBodyLength:
      inByte = Serial.read();
      Serial.println("Action byte 1: "+ String(inByte));
      Serial.println("Action byte 1a: "+ String(inByte<<8));
      currentMessage.bodyLength = inByte<<8;  
      while (!Serial.available()) {
      }     
      inByte = Serial.read();
      currentMessage.bodyLength+=inByte;
      Serial.println("Action byte 2: "+ String(inByte));
      Serial.println("bodyLength: "+ String(currentMessage.bodyLength));
      readBodyIndex = 0;
      handleMessageReceived();
      if (currentMessage.bodyLength != 0)
        readState = readbody;     
      else
        readState = readAction;
      break;
    case readbody:
      pcBufferReadLength = min(32, currentMessage.bodyLength - readBodyIndex);      
      for (byte i=0;i< pcBufferReadLength;i++){
        while (!Serial.available())   {
        }   
        pcBuffer[i] = Serial.read();
      }
      readBodyIndex+=pcBufferReadLength;
      handleMessageDataReceived();
      if (readBodyIndex >= currentMessage.bodyLength){
        Serial.println("Finish message read");
        readState = readAction;
      }
      break;
    }   
  }
}

void handleMessageReceived(){
  Serial.println("received action: "+String(currentMessage.action)+" with body length "+String(currentMessage.bodyLength));
  Serial.println("DPR");
  //return;
  if (currentMessage.action == 7)
    pressZotacButton();
  else if (currentMessage.action == 10)
    startMotor();
  else if (currentMessage.action == 11)
    stopMotor();   
  else if (currentMessage.action == 12){
  } 
  else if (currentMessage.action == 20)
    spinPowerOff();   
  else if (currentMessage.action == 21)
    spinPowerOn();   
  else
    sendRFMessage(currentMessage.action, currentMessage.bodyLength);
}

void handleMessageDataReceived(){
  Serial.println("received data pack of length: "+String(pcBufferReadLength)+". Total received: "+String(readBodyIndex));//+". data: "+String((char*) pcBuffer));
  Serial.println("DPR");
  //return;
  if (currentMessage.action == 12){
    int speed = pcBuffer[0];
    speed = speed<<8;
    speed+=pcBuffer[1];
    setMotorSpeed(speed);
  }
  else
    sendRFData(pcBuffer, pcBufferReadLength);
}






















