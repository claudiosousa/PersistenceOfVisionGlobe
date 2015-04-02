
unsigned int sensorPin = 2;
unsigned long lastDelay = 0;
volatile boolean doIt = false;

void setup(){
  pinMode(sensorPin, INPUT);
  Serial.begin(9600);  
  attachInterrupt(0, doCount, FALLING);
}

void loop() { 
  if (doIt){
    unsigned long now = micros();
    unsigned long delay = now - lastDelay;
    Serial.println(String(1000000/delay) + "\t"+String(delay));
    lastDelay = now;
    doIt = false;
  }
}

void doCount(){
  doIt = true;
}

