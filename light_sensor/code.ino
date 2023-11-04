#define ledPin 10
#define sensorPin A0

int LED_ACTIVATION_VALUE = 400;
int SERIAL_OUTPUT_FREQUENCY = 1000;
int sensorValue = 0;
int ledStatus = 0;
unsigned long prevTime = 0;

void setup() {
  
  pinMode(ledPin, OUTPUT);
  pinMode(sensorPin, INPUT);
  Serial.begin(9600);
}

void loop() {
  
  sensorValue = analogRead(sensorPin);
  
  if (sensorValue < LED_ACTIVATION_VALUE) {
    digitalWrite(ledPin, HIGH);
    ledStatus = 1;
  } else {
  
    digitalWrite(ledPin, LOW);
    ledStatus = 0;
  }
  
  unsigned long currentTime = millis();
  if (currentTime > prevTime + SERIAL_OUTPUT_FREQUENCY) {
    Serial.print("LIGHT SENSOR: ");
    Serial.println(sensorValue);
    Serial.print("LED STATUS: ");
    if (ledStatus == 1) {
      Serial.println("ON");
    } else {
      Serial.println("OFF");
    }
    Serial.println();
    prevTime = currentTime;
    
  }
}
