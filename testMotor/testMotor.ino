unsigned int potPin = A0;    
unsigned int motorPin = 11;
unsigned int ledPin = 13;      
unsigned int sensorValue = 0;  

void setup() {
  Serial.begin(9600);
  
  // declare the ledPin as an OUTPUT:
  pinMode(ledPin, OUTPUT);  
}

void loop() {
  // read the value from the sensor:
  sensorValue = analogRead(potPin);    
  Serial.println(sensorValue);
  analogWrite(motorPin, sensorValue);
}
