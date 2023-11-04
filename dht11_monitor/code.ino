#include <DHT.h>
#include <DHT_U.h>
#include <LiquidCrystal_I2C.h>

#define DHT11_PIN 7
#define buttonPin 2
DHT dht(DHT11_PIN, DHT11);


LiquidCrystal_I2C lcd(0X27,16,2); 
uint8_t previousState;
char LCD_LANGUAGE = 'T'; 

void setup(){
  lcd.init();
  lcd.backlight();
  dht.begin();
  previousState = digitalRead(buttonPin);
}

void loop(){
  
    float tempC = dht.readTemperature();
    float hum = dht.readHumidity();
    uint8_t btn = digitalRead(buttonPin);
    if (btn == LOW && previousState == HIGH) {
      if (LCD_LANGUAGE == 'E') {
        LCD_LANGUAGE = 'T';
      } else {
        LCD_LANGUAGE = 'E';
      }
    }
    previousState = digitalRead(buttonPin);
    lcd.setCursor(0, 0);

    if (LCD_LANGUAGE == 'E') {
      lcd.print("TEM(F):");
      float tempF = tempC * 1.8 + 32;
      lcd.setCursor(7, 0);
      lcd.print(tempF);
      lcd.print(" ");
      lcd.setCursor(14, 0);
      lcd.print("EN\n");
    } else {
      lcd.print("SIC(C):");
      lcd.setCursor(7, 0);
      lcd.print(tempC);
      lcd.print(" ");
      lcd.setCursor(14, 0);
      lcd.print("TR\n");
    }

    lcd.setCursor(0, 1);

    if (LCD_LANGUAGE == 'E') { 
      lcd.print("HUM(%):");
      lcd.print(hum);
    } else {
      lcd.print("NEM(%):");
      lcd.print(hum);
    }
  

  
}
