#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);

const int trigPin = 7;
const int echoPin = 6;
const int buzzPin = 10;
const int ledPin = 13;

int BUZZER_LED_FREQ_MAX = 1000;
int BUZZER_LED_FREQ_MIN = 10;
int DIST_MAX = 100;
int DIST_MIN = 10;
int CURRENT_DIST = 0;
int CURRENT_FREQ = 0;
int UPDATE_FREQ_BUZZER = 200;
int UPDATE_FREQ_LCD    = 200;
float duration, distance;

unsigned long last_buzzer_update = 0;
unsigned long last_lcd_update = 0;

void setup() {
  lcd.init();
  lcd.backlight();
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buzzPin, OUTPUT);
  pinMode(ledPin, OUTPUT);
  lcd.setCursor(0, 0);
  lcd.print("DISTANCE:");
  lcd.setCursor(0, 1);
  lcd.print("FREQUENCY:");
  Serial.begin(9600);
}

void loop() {
  unsigned long current_time = millis();
  noTone(buzzPin);
  if (current_time - last_buzzer_update >= UPDATE_FREQ_BUZZER) {
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    duration = pulseIn(echoPin, HIGH);
    distance = (duration / 2.0) * 0.0343;

    if (distance < DIST_MIN) {
      CURRENT_DIST = (int)distance;
      CURRENT_FREQ = BUZZER_LED_FREQ_MAX;
      digitalWrite(buzzPin, HIGH);
      digitalWrite(ledPin, HIGH);
    } else if (distance > DIST_MAX) {
      CURRENT_DIST = (int)distance;
      CURRENT_FREQ = 0;
      digitalWrite(buzzPin, LOW);
      digitalWrite(ledPin, LOW);
    } else {
      CURRENT_DIST = (int)distance;
      CURRENT_FREQ = ((CURRENT_DIST - DIST_MIN) / (float)(DIST_MAX - DIST_MIN)) * (BUZZER_LED_FREQ_MAX - BUZZER_LED_FREQ_MIN) + BUZZER_LED_FREQ_MIN;
      activateLedAndBuzz(CURRENT_FREQ);
    }
    last_buzzer_update = current_time;
  }

  if (current_time - last_lcd_update >= UPDATE_FREQ_LCD) {
    lcd.setCursor(10, 0);
    lcd.print(CURRENT_DIST);
    lcd.print("cm    ");
    lcd.setCursor(11, 1);
    lcd.print(CURRENT_FREQ);
    lcd.print("ms    ");
    last_lcd_update = current_time;
  }
}

void activateLedAndBuzz(int duration){
  digitalWrite(ledPin, HIGH);
  tone(buzzPin, CURRENT_FREQ);
  delay(duration);
  digitalWrite(ledPin, LOW);
  if(duration == CURRENT_FREQ){
    noTone(buzzPin);
  }
  delay(duration);
}
