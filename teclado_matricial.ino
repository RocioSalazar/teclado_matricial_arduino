#include <Keypad.h>
#include "Wire.h" // For I2C
#include "LCD.h" // For LCD
#include "LiquidCrystal_I2C.h"

const byte ren = 4;
const byte col = 4;
String valor = "";
String contra = "241019A";
int pin13 = 13, pin12 = 12, pin3 = 3;

char keys[ren][col] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', ' '},
  {'*', '0', '#', 'D'}
};
const byte renPin[ren] = {11, 10, 9, 8};
const byte colPin[col] = {7, 6, 5, 4};
Keypad keypad = Keypad(makeKeymap(keys), renPin, colPin, ren, col);
LiquidCrystal_I2C lcd(0x27, 16, 2);
void setup() {
  pinMode(pin13, OUTPUT);  pinMode(pin12, OUTPUT);  pinMode(pin3, OUTPUT);
  Serial.begin(9600);
  lcd.init();
  lcd.begin (16, 2); // 16 x 2 LCD module
  lcd.setBacklight(HIGH);
  lcd.setCursor(0, 0);
  lcd.print(" Seguridad ERSC");
}

void loop() {
  char key = keypad.getKey();
  if (key) {
    lcd.setCursor(0, 0);
    lcd.print("                ");
    lcd.setCursor(0, 0);
    lcd.print(" Seguridad ERSC");
    lcd.setCursor(0, 1);
    lcd.print("                ");
    Serial.print(key);
    lcd.setCursor(0, 1);
    valor = valor + key;
    if (key == ' ') {
      valor = "";
      digitalWrite(pin13, LOW);
      digitalWrite(pin12, LOW);
      digitalWrite(pin3, LOW);
    }
    lcd.print(valor);
    if (valor.length() == 7) {
      if (valor == contra) {
        lcd.setCursor(0, 0);
        lcd.clear();
        lcd.print("     Acceso     ");
        lcd.setCursor(0, 1);
        lcd.print("    Correcto  ");
        digitalWrite(pin13, LOW);
        digitalWrite(pin12, HIGH); digitalWrite(pin3, HIGH); delay(200); digitalWrite(pin12, LOW); digitalWrite(pin3, LOW); delay(200);
        digitalWrite(pin12, HIGH); digitalWrite(pin3, HIGH); delay(200); digitalWrite(pin12, LOW); digitalWrite(pin3, LOW); delay(200); 
        digitalWrite(pin12, HIGH); delay(200);
        digitalWrite(pin3, LOW); delay(500);

        valor = "";
      } else {
        lcd.setCursor(0, 0);
        lcd.clear();
        lcd.print("     Acceso     ");
        lcd.setCursor(0, 1);
        lcd.print("    Denegado  ");
        digitalWrite(pin12, LOW);
        digitalWrite(pin13, HIGH); digitalWrite(pin3, HIGH); delay(500); digitalWrite(pin13, LOW); digitalWrite(pin3, LOW); delay(500);
        digitalWrite(pin13, HIGH); digitalWrite(pin3, HIGH); delay(500); digitalWrite(pin13, LOW); digitalWrite(pin3, LOW); delay(500); digitalWrite(pin13, HIGH); digitalWrite(pin3, HIGH); delay(500);
        digitalWrite(pin3, LOW); delay(500);
        valor = "";
      }
    }

    /*else{
      lcd.setCursor(0,0);
      lcd.print("     Acceso     ");
      lcd.setCursor(0,1);
      lcd.print("    Denegado  ");
      }*/
  }
}
