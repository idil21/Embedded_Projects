const int motorEnablePin = 12;
int motorPin1 =  10;   
int motorPin2 =  11;
const int leftButtonPin = A4;
const int rightButtonPin = A3;
int motorSpeed = 0;
int motorDirection = 1;
const int MOTOR_STEPS = 10;
int segmentPins[] = {2,3,4,5,6,7, 8,9}; 

void setup(){
  pinMode(leftButtonPin, INPUT_PULLUP);
  pinMode(rightButtonPin, INPUT_PULLUP);
  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);
  pinMode(motorEnablePin, OUTPUT);
  for (int i = 0; i < 8; i++) {
    pinMode(segmentPins[i], OUTPUT);
  }
  Serial.begin(9600);
  displayNumber(motorSpeed);
}
  
void loop(){
  if (digitalRead(leftButtonPin) == HIGH) {
    if (motorDirection == 1) {
      if (motorSpeed > 0) {
        motorSpeed -= 1;
      } else {
        motorDirection = 0;
        motorSpeed = 1;
      }
    } else {
      motorSpeed = min(motorSpeed + 1, MOTOR_STEPS);
    }
    updateMotor();
    delay(300);
  }

  if (digitalRead(rightButtonPin) == HIGH) {
   if (motorDirection == 0) {
      if (motorSpeed > 0) {
        motorSpeed -= 1;
      } else {
        motorDirection = 1;
        motorSpeed = 1;
      }
    } else {
      motorSpeed = min(motorSpeed + 1, MOTOR_STEPS);
    }
    updateMotor();
    delay(300);
  }
  displayNumber(motorSpeed);
}


void updateMotor() {
  if (motorDirection == 1) {
    digitalWrite(motorPin1, HIGH);
    digitalWrite(motorPin2, LOW);
  } else {
    digitalWrite(motorPin1, LOW);
    digitalWrite(motorPin2, HIGH);
  }
  int speedValue = map(motorSpeed, 0, MOTOR_STEPS, 127, 1023);
  Serial.println(speedValue);
  analogWrite(motorEnablePin,speedValue);
}
void displayNumber(int number) {
  
byte segments[16][8] = {
    {0, 0, 0, 0, 0, 0, 1,1}, // 0
    {1, 0, 0, 1, 1, 1, 1,1}, // 1
    {0, 0, 1, 0, 0, 1, 0,1}, // 2
    {0, 0, 0, 0, 1, 1, 0,1}, // 3
    {1, 0, 0, 1, 1, 0, 0,1}, // 4
    {0, 1, 0, 0, 1, 0, 0,1}, // 5
    {0, 1, 0, 0, 0, 0, 0,1}, // 6
    {0, 0, 0, 1, 1, 1, 1,1}, // 7
    {0, 0, 0, 0, 0, 0 ,0,1}, // 8
    {0, 0, 0, 0, 1, 0, 0,1},  // 9
    {0, 0, 0, 1, 0, 0, 0,1},  // A
    {1, 1, 0, 0, 0, 0, 0,1},  // b
    {0, 1, 1, 0, 0, 0, 1,1},  // C
    {1,0, 0, 0, 0, 1, 0,1},  // d
    {0, 1, 1, 0, 0, 0, 0,1},  // E
    {0, 1, 1, 1, 0, 0, 0,1}   // F
  };
  for (int i = 0; i < 8; i++) {
    digitalWrite(segmentPins[i], segments[number][i]);
  }
}