#include <LiquidCrystal_I2C.h>
#include <Wire.h>

// 16 by 2 I2C LCD display :
LiquidCrystal_I2C lcd(0x27,  16, 2);

// Time variables
int sec = 0;
int min = 0;
int hrs = 0;
void setup() {
// Lcd init
  lcd.init();
  lcd.backlight();
}

void loop() {
  // 999 ms delay (because the code makes 1ms to be looped, not sure though)
  delay(999);
  // Time math
  if (sec <= 59) {
    sec = sec + 1;
  }
  if (min == 60) {
    sec = 0;
    min = min + 1;
  }
  if (min == 60) {
    min = 0;
    hrs = hrs + 1;
  }
  if (hrs == 24) {
    hrs = 0;
  }
  // Format HH:MM:SS (24h of course), prints a 0 if the time is less than 10 (to be fancier)
  lcd.setCursor(4, 0);
  if (hrs < 10) {
  lcd.print("0");
  lcd.print(hrs);
  }
  else {
    lcd.print(hrs);
  }
  lcd.print(":");
  if (min < 10) {
    lcd.print("0");
    lcd.print(min);
  }
  else {
    lcd.print(min);
  }  
  lcd.print(":");
  if (sec < 10) {
  lcd.print("0");
  lcd.print(sec);
  }
  else {
    lcd.print(sec);
  }
  
  

}
