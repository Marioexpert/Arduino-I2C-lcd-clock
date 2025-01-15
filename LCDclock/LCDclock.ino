#include <LiquidCrystal_I2C.h>
#include <Wire.h>

// 16 by 2 I2C LCD display :
LiquidCrystal_I2C lcd(0x27,  16, 2);

// Time Variables :
int sec = 0;
int min = 0;
int hrs = 0;
int hrs12 = 12;

// Serial buffer :
int data = 0;

// Flags :
int blink = 0;
int ampmflag = 0;
int curs = 4;

void setup() {
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
}


void getClock() {

// Checks for serial activity :
  if (Serial.available()) {
      lcd.clear();
    
    // Wait for the letters : H (Hour), M(Minutes), S(Seconds) and T(Type of display 12h/24h), then it reads the 2 next characters
         char data = Serial.read();
         if (data == 'H') {
          hrs = 0;
          hrs = Serial.read() - 48;
          hrs = hrs*10 + (Serial.read() - 48 );
          
            if (hrs >= 13) {
              hrs12 = hrs - 12;
             }

            else if (hrs < 13) {
              hrs12 = hrs;
             }

          }
         

         else if (data == 'M') {
          min = 0;
          min = Serial.read() - 48;
          min = min*10 + (Serial.read() - 48 );
         }

          else if (data == 'S') {
          sec = 0;
          sec = Serial.read() - 48;
          sec = sec*10 + (Serial.read() - 48 );
          }

          else if (data == 'T') {
            ampmflag = 0;
            ampmflag = Serial.read() - 48;
          }

// Error verification. If an error is present, the variable concerned will be set to default :
   }
         if (hrs >= 24) {
          Serial.print("Invalid clock!");
          Serial.print("Format Hhh");
          hrs = 0;
          getClock();
         }

         if (hrs12 >= 13) {
          Serial.print("Invalid clock!");
          Serial.print("Format Hhh");
          hrs12 = 12;
          getClock();
         }

         else if (min >= 60) {
          Serial.print("Invalid clock!");
          Serial.print("Format Mmm");
          min = 0;
          getClock();
         }

         else if (sec >= 60) {
          Serial.print("Invalid clock!");
          Serial.print("Format Sss");
          sec = 0;
          getClock();
         }

         else if (ampmflag > 1) {
          Serial.print("Invalid setting!");
          Serial.print("O = 12h / 1 = 24h");
          Serial.print("Default will be set (24h)");
          ampmflag = 0;
          getClock();
         }


 }
 
void loop() {

// 988ms delay (Arduino's clock isn't precise)
      delay(988);

// Time math :
          if (sec <= 59) {
            sec = sec + 1;
          }

          if (sec == 60) {
            sec = 0;
            min = min + 1;
          }

          if (min == 60) {
            min = 0;
            hrs = hrs + 1;
            hrs12 = hrs12 + 1;
          }

          if (hrs == 24) {
            hrs = 0;
          }

          if (hrs12 == 13) {
            hrs12 = 1;
          }

          if (hrs12 == 0) {
            hrs12 = 12;
          }  
            
        if (ampmflag == 1) {
            curs = 2;
        }
        else {
            curs = 4;
        }

// Prints the time with the folowing format : HH:MM:SS (AM/PM)*
// * means that it's set by the user (enable or disable the feature)

// Change the cursor position to have the clock centered (i like fanciness)
  lcd.setCursor(curs, 0);

    if (ampmflag == 0) {
      if (hrs < 10) {
          lcd.print("0");
          lcd.print(hrs);
      }

      else {
        lcd.print(hrs);
      }
            
    }
              

    else if (ampmflag == 1) {
      if (hrs12 < 10) {
        lcd.print("0");
        lcd.print(hrs12);
      }

      else {
        lcd.print(hrs12);
      }

    }

// The ":" blink routine :

    if (blink == 0) {
        blink = blink + 1;
        lcd.print(":"); 
    }

      else {
        lcd.print(" "); 
        blink = 0;      
    }
    

// If there is only 1 digit to display, the Arduino adds a 0 before it (Fanciness, again)  
    if (min < 10) {
          lcd.print("0");
          lcd.print(min);
          }

        else {
          lcd.print(min);
        }  

     if (blink == 1) {
        lcd.print(":"); 
    }

      else {
        lcd.print(" ");    
    }

    if (sec < 10) {
          lcd.print("0");
          lcd.print(sec);
        }

        else {
          lcd.print(sec);
        }
    if (ampmflag == 1) {
       if (hrs < 12) {
        lcd.print("  AM");
       }

       else {
        lcd.print("  PM");
       }
    }        

// The clock can be modified on the fly :

      getClock();

}


    

     



