#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);
boolean SCROLL_FLAG = true;
int SCROLL_WAIT = 1000;
char SCROLL_DIRECTION = 'L';
char LCD_ROW_1[] = "This text is for row 0 and longer than 16 characters.";
char LCD_ROW_2[] = "ABCD EFGH       ";
int lcd_row1_len;
int lcd_row2_len;
void setup() {
  lcd.init();
  lcd.backlight();
  lcd_row1_len = strlen(LCD_ROW_1);
  lcd_row2_len = strlen(LCD_ROW_2);
  lcd.clear();
}

void loop() {
  int length = 16;
    int i, j;
    if(SCROLL_FLAG){
      if(SCROLL_DIRECTION == 'L'){
        for (i = 0; i < min(lcd_row1_len,lcd_row2_len); i++) {
            // Clear the LCD screen
            lcd.clear();
            for (j = 0; j < length; j++) {
                // Print the current character of the string on the first line
                lcd.print(LCD_ROW_1[(j + i) % lcd_row1_len]);
                 
            }
            // Move the cursor to the second line of the LCD screen
            lcd.setCursor(0, 1);
            for (j = 0; j < length; j++) {
                // Print the current character of the string on the second line
                lcd.print(LCD_ROW_2[(j + i) % lcd_row2_len]);
            }
            delay(SCROLL_WAIT);  
        }  
      }
      else if(SCROLL_DIRECTION == 'R'){
        for (i = min(lcd_row1_len,lcd_row2_len)-1; i >= 0; i--) {
            // Clear the LCD screen
            lcd.clear();
            for (j = 0; j < length; j++) {
                // Print the current character of the string on the first line
                lcd.print(LCD_ROW_1[(j + i) % lcd_row1_len]);
                 
            }
            // Move the cursor to the second line of the LCD screen
            lcd.setCursor(0, 1);
            for (j = 0; j < length; j++) {
                // Print the current character of the  string on the second line
                lcd.print(LCD_ROW_2[(j + i) % lcd_row2_len]);
            }
            delay(SCROLL_WAIT);  
        }  
      }
      
    }
    else{
      lcd.setCursor(0, 0);
      lcd.print(LCD_ROW_1);
      lcd.setCursor(0, 1);
      lcd.print(LCD_ROW_2);
    }

}