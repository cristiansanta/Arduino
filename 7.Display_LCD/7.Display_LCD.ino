#include <LiquidCrystal.h>

LiquidCrystal lcd(10, 9, 8, 5, 4, 3, 2);//(RS, RW, E, D4, D5, D6, D7)

void setup() {
  lcd.begin(16,2);// put your setup code here, to run once:
  lcd.setCursor(0,0);
  lcd.print("MI PROPOSITO SER MEJOR QUE AYER");
  lcd.setCursor(3,1);
  lcd.print("FEARLESS");
}

void loop() {
  //Desplazar ahacia la izquierda
      lcd.scrollDisplayRight();
      delay(100);
      lcd.noCursor();//APAGAR CURSOR
      delay(100);

      lcd.cursor();//ENCENDER CURSOR
      delay(100);
}
