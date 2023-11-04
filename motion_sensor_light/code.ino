int ledPin = 13;
int sensorPin = 10;
int segmentPins[] = {2,3, 4, 5, 6, 7, 8, 9}; 

int TIMER_START = 23; 
int TIMER_SPEED = 300; 
int ANIMATION_SPEED = 300; 

int remainingTime; 
int currentSegment=0; 

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(sensorPin, INPUT);
   
  for (int i = 0; i < 8; i++) {
    pinMode(segmentPins[i], OUTPUT);
    digitalWrite(segmentPins[i], HIGH);
  }
  digitalWrite(ledPin, LOW);
  remainingTime = TIMER_START;
}

void loop() {
  if (digitalRead(sensorPin) == HIGH) {
    countdown(); 
  }
  
}

void countdown() {
  while (remainingTime >= 0) {
    digitalWrite(ledPin, HIGH);
    if(remainingTime <= 15)
    {
      displayNumber(remainingTime);
    }
    else
    {
       updateAnimation();
    }

 
    delay(TIMER_SPEED);
    remainingTime--;
  }
  digitalWrite(ledPin, LOW);
 
  for (int i = 2; i <= 9; i++) {
  digitalWrite(i, HIGH);
  }
  //digitalWrite(ledPin, LOW);
  
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
void updateAnimation() {
  digitalWrite(segmentPins[currentSegment], LOW);
  delay(ANIMATION_SPEED);
  digitalWrite(segmentPins[currentSegment], HIGH);
  if (currentSegment >8) {
    currentSegment = 0;
  }
  currentSegment++;
}