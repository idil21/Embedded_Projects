#include <DHT.h>

#include <DHT_U.h>
#include <LiquidCrystal_I2C.h>
#include "string.h"
#define DHT11_PIN 7
DHT dht(DHT11_PIN, DHT11);


LiquidCrystal_I2C lcd(0X27,16,2); 

const int lightPin = A0;
int TEMPERATURE_MIN = 25;
int TEMPERATURE_MAX = 35;
int HUMIDITY_MIN = 30;
int HUMIDITY_MAX = 70;
int LIGHT_MIN = 300;
int LIGHT_MAX = 700;
String minLabel;
String curLabel;
String maxLabel;


void setup(){
  lcd.init();
  lcd.backlight();
  dht.begin();
  pinMode(lightPin,INPUT);
  Serial.begin(9600);
  
}

void loop(){
  
    float temperature = dht.readTemperature();
    float humidity = dht.readHumidity();
    int lightValue = map(analogRead(lightPin), 0, 1023, 0, 1000);
    Serial.print("temperature = ");
    Serial.println(temperature);
    Serial.println();
     Serial.print("humidity = ");
    Serial.println(humidity);

    checkSensor("TEMP", temperature, TEMPERATURE_MIN, TEMPERATURE_MAX);
    delay(500);
    checkSensor("HUMI", humidity, HUMIDITY_MIN, HUMIDITY_MAX);
    delay(500);
    checkSensor("LIGH", lightValue, LIGHT_MIN, LIGHT_MAX);
    delay(500);
    if(lightValue < LIGHT_MAX && lightValue > LIGHT_MIN && humidity < HUMIDITY_MAX &&
      humidity > HUMIDITY_MIN && temperature < TEMPERATURE_MAX && temperature > TEMPERATURE_MIN){
      displayOptimalValues(temperature, humidity, lightValue);
    
    }
    delay(500); 
   
}

void checkSensor(const char* sensorName, int value, int minValue, int maxValue) {
  if (value > maxValue) {
    displayTooHigh(sensorName, value, maxValue);
    delay(500);
  } else if (value < minValue) {
    displayTooLow(sensorName, value, minValue);
    delay(500);
  }
}

void displayOptimalValues(int temperature, int humidity, int light) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("T: ");
  lcd.print(temperature);
  lcd.print(" H:");
  lcd.print(humidity);
  lcd.print(" L:");
  lcd.print(light);
  
  lcd.setCursor(0, 1);
  lcd.print("STATUS: OPTIMAL");
}

void displayTooHigh(const char* sensorName, int value, int maxValue) {
  lcd.clear();
  lcd.print(String(sensorName) + " IS TOO HIGH");
  
  lcd.setCursor(0, 1);
  if (sensorName == "TEMP") {
    maxLabel = "TMAX:";
    curLabel = " TCUR:";

  } else if (sensorName == "HUMI") {
    maxLabel = "HMAX:";
    curLabel = " HCUR:";

  } else {
    maxLabel = "LMAX:";
    curLabel = "LCUR:";
  }
  lcd.print(maxLabel);
  lcd.print(maxValue);
  lcd.print(curLabel);
  lcd.print(value);
}

void displayTooLow(const char* sensorName, int value, int minValue) {
  lcd.clear();
  lcd.print(String(sensorName) + " IS TOO LOW");
  
  lcd.setCursor(0, 1);
  
  if (sensorName == "TEMP") {
    minLabel = "TMIN:";
    curLabel = " TCUR:";
  } else if (sensorName == "HUMI") {
    minLabel = "HMIN:";
    curLabel = " HCUR:";
  } else {
    minLabel = "LMIN:";
    curLabel = "LCUR:";
  }
  lcd.print(minLabel);
  lcd.print(minValue);
  lcd.print(curLabel);
  lcd.print(value);
}

