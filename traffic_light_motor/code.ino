#define ledPin 2
#define sensorPin A0
const int motorEnablePin = 12;
int motorPin1 =  10;   
int motorPin2 =  11;
int LED_ACTIVATION_VALUE = 70;
int LED_WAIT_DURATION_MIN = 2000;
int LED_WAIT_DURATION_MAX = 6000;
int LED_ON_DURATION_MIN = 2000;
int LED_ON_DURATION_MAX = 6000;
int LIGHT_SENSOR_OUTPUT_INTERVAL = 1000;

int ledState = 0;
int randomTime =0;
unsigned long prevTime = 0;
unsigned long sensorOutTime=0;
void setup()
{
  pinMode(ledPin,OUTPUT);
  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);
  pinMode(motorEnablePin, OUTPUT);
  pinMode(sensorPin,INPUT);
  Serial.begin(9600);
  digitalWrite(motorPin1, LOW);
  digitalWrite(motorPin2, HIGH);
  analogWrite(motorEnablePin,255);
  digitalWrite(ledPin, LOW); 
}

void loop()
{
  unsigned long currentTime = millis();
  if (ledState) {
    randomTime = random(LED_ON_DURATION_MIN, LED_ON_DURATION_MAX);
  } else {
    randomTime = random(LED_WAIT_DURATION_MIN, LED_WAIT_DURATION_MAX);
  }
  
   if (currentTime - prevTime > randomTime) {
    ledState = !ledState;
    digitalWrite(ledPin, ledState);
    prevTime = currentTime;
    Serial.print("LED is turned ");
    Serial.print(ledState ? "ON" : "OFF");
    Serial.print(" for ");
    Serial.print(randomTime);
    Serial.println(" milliseconds.");
   }
  
   int lightSensorValue = analogRead(sensorPin);
   if (lightSensorValue > LED_ACTIVATION_VALUE) {
    digitalWrite(motorPin1, LOW);
    digitalWrite(motorPin2, LOW);
     analogWrite(motorEnablePin,0);
   } else {
    digitalWrite(motorPin1, LOW);
    digitalWrite(motorPin2, HIGH);
    analogWrite(motorEnablePin,255);
   }
    
    if (currentTime - sensorOutTime > LIGHT_SENSOR_OUTPUT_INTERVAL) {
    Serial.print("Light sensor output is ");
    Serial.println(lightSensorValue);
    sensorOutTime = currentTime;
  }
  
}