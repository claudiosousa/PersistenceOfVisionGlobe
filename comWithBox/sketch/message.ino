void setupMessaging(){
  Serial.begin(115200);
  Serial.println("Arduino started...");
}


unsigned long i=0;
enum  messageReadState{  
  readAction,
  readBodyLength,
  readbody
};


byte readBodyIndex = 0;

struct currentMessageType{  
  byte action;
  byte bodyLength;
  byte body[255];
};

messageReadState readState = readAction;
currentMessageType currentMessage;

void readMessage(){
  while (Serial.available()) {
    byte inByte = Serial.read();
    switch(readState)  {
    case readAction:
      currentMessage.action = inByte;
      readState = readBodyLength;
      break;
    case readBodyLength:
      currentMessage.bodyLength = inByte;            
      readBodyIndex = 0;
      if (inByte != 0){
        readState = readbody;
      }
      else{
        handleMessage();
        readState = readAction;
      }      
      break;
    case readbody:
      currentMessage.body[readBodyIndex] = inByte;
      readBodyIndex++;

      if (readBodyIndex >= currentMessage.bodyLength){
        handleMessage();
        readState = readAction;
      }
      break;
    }   
  }
}

void handleMessage(){
  if (currentMessage.action == 0)
    stopMotor();
  else if (currentMessage.action == 1)
    startMotor();
}




