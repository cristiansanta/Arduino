const int pot=A1;
float RES;
float volts;
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x3F,16,2);

void setup() {
    // lcd.begin(16, 2);
     lcd.init();//inicia led
  lcd.backlight();
   analogReference(DEFAULT);
  //   analogReference(EXTERNAL);//CON ESTO EL ARDUINO SABE QUE LA ENTRADA MAXIMA ES DE 3.3V y habilita los 1023 bits maximos para la señal de 3.3
}

void loop() {
 RES = analogRead(pot);
 volts=RES*5/1023.0;//----> analogReference(DEFAULT);
 //volts=RES*3.3/1023.0;//----> analogReference(EXTERNAL);

  lcd.home();
  lcd.print("POT-volts: ");
  lcd.print(volts);
  lcd.setCursor(0,1);
  lcd.print("POT-int: ");
  lcd.print(RES);
  
  delay(500);
  lcd.clear();
}
