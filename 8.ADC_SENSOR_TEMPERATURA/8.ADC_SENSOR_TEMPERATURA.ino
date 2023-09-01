#include <LiquidCrystal.h>;
LiquidCrystal lcd(10,8,5,4,3,2);
const int TMP36= A0;
float temperature=0.0;
float voltaje=0.0;

void setup() {
  Serial.begin(9600);
  lcd.begin(16,2);// put your setup code here, to run once:
  lcd.home();//lcd.setCursor(0,0);
  lcd.print("SENSOR TEMPERATURA");
  lcd.setCursor(1,1);
  lcd.print("LM35:");
}

void loop() {
      float n=analogRead(TMP36);  //Almacena valor del sensor
      voltaje=(n*5/1023.0);      //CONVIERTE VALOR flotante del sensor EN TENSION=V
      temperature=((float(analogRead(TMP36))*5.0)/1023.0)/0.01;

      Serial.print("POT Int: \t");
      Serial.print(analogRead(TMP36));
      Serial.print(" -- POT Volts: ");
      Serial.println(voltaje);
      delay(1000);
      
      lcd.setCursor(7, 1);
      lcd.print(temperature);
      lcd.setCursor(14, 1);
      lcd.print("C");
//      lcd.noCursor();
//      delay(500);
//      lcd.cursor();
//      delay(500);
}
