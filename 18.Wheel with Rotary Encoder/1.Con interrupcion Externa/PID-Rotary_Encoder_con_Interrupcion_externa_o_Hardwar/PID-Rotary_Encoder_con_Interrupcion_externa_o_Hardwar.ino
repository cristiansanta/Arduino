#include <util/atomic.h>
#include <LiquidCrystal.h>
LiquidCrystal lcd(14, 13, 12, 11, 10, 9); //A0=14

int DT = 2;// DT a pin digital 2 (DT en modulo) Pin de la INTERRUPCION
int CLK = 4;// CLK a pin digital 3 (CLK en modulo)
#define SW 3

volatile int Posicion_Encoder = 0;

const float pi = 3.14;//Número PI
const float R = 3.25;//radius of wheel
const int N = 40;//steps per rotation///Los pasos por rotación dependen del codificador rotatorio que se puede cambiar de 8 a 48

float distance = 0;

int EN1 = 5;//Inyectar PWM para controlar velocidad motor
int engine_1 = HIGH, engine_2 = LOW;
//byte PWM=75;//VELOCIDAD MOTOR--->REEMPLAZADO POR PID

// globals
long prevT = 0;
int posPrev = 0;

float v1Filt = 0;
float v1Prev = 0;

float eintegral = 0;

void setup() { 
  pinMode (DT ,INPUT);
  pinMode (CLK ,INPUT);
  pinMode(SW, INPUT);
  pinMode(7, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(EN1, OUTPUT);
  
  lcd.begin(16, 2);
  lcd.print("MEASURNING WHEEL");
  
   attachInterrupt(digitalPinToInterrupt(DT),interrupt,RISING);//Interrupcion Externa
   attachInterrupt(digitalPinToInterrupt(SW),SWITCH,RISING);//INTERRUPCION PARA EL SWITCH
}
void SWITCH(){//INTERRUPCION EXTERNA
  engine_1=!engine_1;
  engine_2=!engine_2;
}

void loop() {
  float posi=0;

  ATOMIC_BLOCK(ATOMIC_RESTORESTATE){
  posi=Posicion_Encoder;
  }
  // Compute velocity with method 1-->ESTE
  long currT = micros();
  float deltaT = ((float) (currT-prevT))/1.0e6;
  float velocity1 = (posi - posPrev)/deltaT;  
  posPrev = posi;
  prevT = currT;

  // Convert count/s to RPM
  float v1 = velocity1/600.0*60.0;
  
/*  // Low-pass filter (25 Hz cutoff)
 *     FORMULA:
 *  v_filt[n]=0.854*v_filt[n-1]*0.0728*v[n]+0.0728*v[n-1];
 */
  v1Filt = 0.854*v1Filt + 0.0728*v1 + 0.0728*v1Prev;
  v1Prev = v1;
  
  // Set a target
  float vt = 100*(sin(currT/1e6)>0);

  // Compute the control signal u
  float kp = 5;
  float ki = 10;
  float e = vt-v1Filt;
  eintegral = eintegral + e*deltaT;
  
  float u = kp*e + ki*eintegral;
  float pwr = (float) fabs(u);
  if(pwr > 255){
    pwr = 155;
  }

  digitalWrite(7, engine_1);
  digitalWrite(6, engine_2);
  analogWrite(EN1, pwr);
  
  distance = ((2*pi*R)/N) *  posi;

  lcd.setCursor(0, 1);
  lcd.print(distance);

  lcd.setCursor(7, 1);
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
