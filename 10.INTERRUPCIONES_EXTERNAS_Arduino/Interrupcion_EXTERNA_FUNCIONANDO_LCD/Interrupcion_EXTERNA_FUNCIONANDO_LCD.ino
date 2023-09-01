#include <TimerOne.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
//Crear el objeto lcd  dirección  0x3F y 16 columnas x 2 filas
LiquidCrystal_I2C lcd(0x3F,16,2);
byte aja = 2;
int cont=0;
int AC=0;
long myTime=0;

void setup() {Serial.begin(9600);
  lcd.init();  
  //Encender la luz de fondo.
  lcd.backlight();  
  // Escribimos el Mensaje en el LCD en una posición  central.
  lcd.home();
  lcd.print("CURSO DE ARDUINO");
  lcd.setCursor(0, 1);
    lcd.print(cont);
    attachInterrupt(digitalPinToInterrupt(aja),hagale,RISING);////////////INTERRUPCION EXTERNA conteo con pulsador
}

void loop() {
//  lcd.scrollDisplayLeft(); //  delay(500);
    if(AC!=cont){
    AC=cont;
    Serial.print(cont);
    Serial.print(" ");
    lcd.setCursor(0, 1);
    lcd.print("   ");
    lcd.setCursor(0, 1);
    lcd.print(cont);
    }
}

void hagale()
{
  if(millis() - myTime >200){//antirebore con funcion millis() o la otra opcion es con un while() y delay() LA DIFERENCIA ES QUE CON millis() SI MANTIENE PRESIONADO SIGUE DERECHO EL CONTEO EN CAMBIO CON while() HACE EL CONTEO CUANDO SUELTA EL BOTON
    cont++;

//    Serial.print(cont);
//    Serial.print(" ");
    myTime=millis();
  }
}
