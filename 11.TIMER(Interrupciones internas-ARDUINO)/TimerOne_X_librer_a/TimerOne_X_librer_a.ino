#include <TimerOne.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
//Crear el objeto lcd  dirección  0x3F y 16 columnas x 2 filas
LiquidCrystal_I2C lcd(0x3F,16,2);
volatile long int cont=555;
int ac=0;

void setup() {
  Serial.begin(9600);
  lcd.begin(16,2);
  lcd.init();  
  //Encender la luz de fondo.
  lcd.backlight();  
  // Escribimos el Mensaje en el LCD en una posición  central.
  lcd.home();
  lcd.print("TIMER dE ONE");
    lcd.setCursor(0,1);
  lcd.print(cont);
  Timer1.initialize(250000);//250ms    inicializar TIMER1
  Timer1.attachInterrupt(conteo);///LLAMA FUNCION TIMER1
}

void loop() {//COMO CONLUSION SE DICE QUE LAS INTERRUPCIONES SON INDEPENDIENTES LO QUE QUIERE DE DECIR QUE NO NECESITAN DE LA FUNCION PRINCIPAL *VOID LOOP*

//  digitalWrite(12, HIGH);
//  delay(1500);
//  digitalWrite(12, LOW);
//  delay(1500);
  
  if(ac != cont)
  {ac=cont;
  lcd.setCursor(0,1);
  lcd.print("     ");
  lcd.setCursor(0,1);
  lcd.print(cont);
  Serial.print(cont);
  Serial.print(" ");
  }
}

void conteo(void)//EN LA FUNCION DE INTERRUPCION NO SE DEBE IMPRIMIR COMO BUENA PRACTICA DE PROGRAMACION, SE DEBE IMPRIMIR EN EL VOID LOOP OSEA EL PRINCIPAL
{
  cont--;
  if(cont<0)
  {
    cont=555;
  }
}
