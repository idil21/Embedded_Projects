int SOUND_DURATION = 500;
int SILENCE_DURATION = 50;
int MELODY[] = {1,2,3,4,4,4,4,3,3,3,2,2,2,1,4,4,4,4,3,3,3,2,2,1};
// another doorbell melody 1,2,3,4,4,4,4,3,3,3,2,2,2,1,4,4,4,4,3,3,3,2,2,1
int melodyLength = 0;
int buzzerPin = 7;
int buttonPin = 2;
int buttonState = 0;
int currentNote = 0;

void setup() {
  pinMode(buzzerPin, OUTPUT);
  pinMode(buttonPin, INPUT);
  melodyLength = sizeof(MELODY)/sizeof(MELODY[0]);
}
void loop() {
  buttonState = digitalRead(buttonPin);
  if (buttonState == HIGH) {
    simulateDoorBell();
  }
  
}
void simulateDoorBell() {
  for (currentNote = 0; currentNote < melodyLength; currentNote++) {
    int noteDuration = SOUND_DURATION;
    if (MELODY[currentNote] == 0) {
      noteDuration = SILENCE_DURATION;
    }
    tone(buzzerPin, frequency(MELODY[currentNote]), noteDuration);
    delay(noteDuration);
    noTone(buzzerPin);
    delay(SILENCE_DURATION);
  }
}
int frequency(int note) {
  switch (note) {
    case 0:
      return 0;
    case 1:
      return 262;
    case 2:
      return 294;
    case 3:
      return 330;
    case 4:
      return 349;
    case 5:
      return 392;
    case 6:
      return 440;
    case 7:
      return 494;
    case 8:
      return 523;
  }
}