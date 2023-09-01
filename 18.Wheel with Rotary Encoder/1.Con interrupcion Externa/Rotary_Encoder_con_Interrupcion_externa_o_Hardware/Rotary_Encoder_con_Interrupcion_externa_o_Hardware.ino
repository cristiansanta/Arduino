#include <LiquidCrystal.h>
LiquidCrystal lcd(14, 13, 12, 11, 10, 9); //A0=14

int DT = 2;// DT a pin digital 2 (DT en modulo) Pin de la INTERRUPCION
int CLK = 3;// CLK a pin digital 3 (CLK en modulo)

volatile int Posicion_Encoder = 0;

const float pi = 3.14;//Número PI
const float R = 3.25;//radius of wheel
const int N = 40;//steps per rotation///Los pasos por rotación dependen del codificador rotatorio que se puede cambiar de 8 a 48

float distance = 0;

int EN1 = 5;//Inyectar PWM para controlar velocidad motor
int engine_1 = HIGH, engine_2 = LOW;
byte PWM=75;//VELOCIDAD MOTOR


void setup() { 
  pinMode (DT ,INPUT);
  pinMode (CLK ,INPUT);
  pinMode(7, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(EN1, OUTPUT);
  
  lcd.begin(16, 2);
  lcd.print("MEASURNING WHEEL");
  
   attachInterrupt(digitalPinToInterrupt(DT),interrupt,LOW);//Interrupcion Externa
}

void loop() {
  digitalWrite(7, engine_1);
  digitalWrite(6, engine_2);
  analogWrite(EN1, PWM);
  
  distance = ((2*pi*R)/N) * Posicion_Encoder ;

  lcd.setCursor(0, 1);
  lcd.print( distance);

  lcd.setCursor(5, 1);
  lcd.print("cm Modificado A mi modo"); 
 }

 void interrupt(){//Función llamada por la interrupción //Funcion que determina el sentido del giro del encoder
  static unsigned long LastState=0;// variable static con ultimo valor de tiempo de interrupcion
  unsigned long timeInterrupt = millis();// variable almacena valor de func. millis

  if(timeInterrupt - LastState > 5){// No lee posibles rebotes en pulsos menores a 5 mseg.
    if(digitalRead(CLK)==HIGH){// si CLK es HIGH, rotacion a la derecha
      Posicion_Encoder++;// incrementa posicion del menu en 1
    }
    else{         // si CLK es LOW, rotacion a la izquierda
      Posicion_Encoder--;// decrementa posicion del menu en 1
    }
    LastState = timeInterrupt;//actualiza valor del tiempo tiempo
  }  
}
