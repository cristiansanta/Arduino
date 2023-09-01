#define ledPin 7
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x3F,16,2);
volatile int cont=0;
int var_AUX=0;

void setup()
{Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
  lcd.init();
  lcd.backlight();
  lcd.home();
  lcd.print("CURSO DE ARDUINO");
  // Configuração do timer1 
  TCCR1A = 0;                        // El registro de control A queda todo en 0, pines OC1A y OC1B deshabilitados
  TCCR1B = 0;                        //limpia el registrador
  TCCR1B |= (1<<CS10)|(1 << CS12);   // configura prescaler para 1024: CS12 = 1 e CS10 = 1

  TCNT1 = 0xBDD;//Inicia con 4 segundos                    // inicia timer para desbordamiento 4 segundos
                                     // 65536-(16MHz/1024/(1Hz/4) - 1) = 3037 = 0xBDD
  
  TIMSK1 |= (1 << TOIE1);           // habilita la interrupcion del TIMER1
}

void loop()
{
  if(var_AUX != cont)
  { var_AUX = cont;
  lcd.setCursor(0,1);
  lcd.print("   ");
  lcd.setCursor(0,1);
  lcd.print(cont);
  }
}

ISR(TIMER1_OVF_vect)                              //interrupcion del TIMER1
{
  TCNT1 = 57724.5;//----->500ms=0.5      // Renicia TIMER --  REACARGAR TIMER PARA DESBORDAR y queda ejecutandose con este nuevo valor de segundo asiganado
  cont++;
  Serial.print(cont);
  digitalWrite(ledPin, digitalRead(ledPin) ^ 1); //invierte el estado do led
}
