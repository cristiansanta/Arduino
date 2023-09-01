#include <util/atomic.h> // For the ATOMIC_BLOCK macro
#include <LiquidCrystal.h>
LiquidCrystal lcd(14, 13, 12, 11, 10, 9); //A0=14

#define ENCA 2 // YELLOW
#define ENCB 4 // WHITE

int EN1 = 5;//Inyectar PWM para controlar velocidad motor
int engine_1 = HIGH, engine_2 = LOW;
//const byte PWM_C=255;//VELOCIDAD MOTOR--->REEMPLAZADA POR LA SEÑAL CONTROLADA PID

volatile long posi = 0; // specify posi as volatile: https://www.arduino.cc/reference/en/language/variables/variable-scope-qualifiers/volatile/

const float pi = 3.14;//Número PI
const float R = 3.25;//radius of wheel
const int N = 40;//steps per rotation///Los pasos por rotación dependen del codificador rotatorio que se puede cambiar de 8 a 48

double distance = 0;

long prevT = 0;
float eprev = 0;
float eintegral = 0;

void setup() {
  Serial.begin(9600);
  pinMode(ENCA,INPUT);
  pinMode(ENCB,INPUT);
  pinMode(7, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(EN1, OUTPUT);
  lcd.begin(16, 2);
  lcd.print("PID ENCODER");
  attachInterrupt(digitalPinToInterrupt(ENCA),readEncoder,LOW);
}

void loop() {
  // set target position
  //int target = 1200;
  float target = 250*sin(prevT/1e6);

  // PID constants
  float kp = 1;
  float kd = 0.025;
  float ki = 0.0;

  // time difference
  long currT = micros();
  float deltaT = ((float) (currT - prevT))/( 1.0e6 );
  prevT = currT;
  
  // Read the position in an atomic block to avoid a potential
  // misread if the interrupt coincides with this code running
  // see: https://www.arduino.cc/reference/en/language/variables/variable-scope-qualifiers/volatile/
  long pos = 0; 
  ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
    pos = posi;
  }
//---------------   PID   ---------------//
  // error
  int e = pos - target;
  // derivative
  float dedt = (e-eprev)/(deltaT);
  // integral
  eintegral = eintegral + e*deltaT;
  // control signal
  float u = kp*e + kd*dedt + ki*eintegral;

  // motor power
  float pwr = fabs(u);
  if( pwr > 255 ){
    pwr = 255;
  }
  // motor direction
  int dir = 1;
  if(u<0){
    dir = -1;
  }
  // signal the motor PID recibido para empezar a trabajar en motor
  setMotor(dir, pwr, EN1, 7, 6);//PWM_C=velocidad asignada-->Reemplazada por PWM procesado por PID
  
  // store previous error
  eprev = e;
  
  distance = ((2*pi*R)/N) * pos;
//  Serial.println(pos);
    lcd.setCursor(0, 1);
    lcd.print(distance);
    lcd.setCursor(6, 1);
    lcd.print("cm");
    lcd.setCursor(9, 1);
    lcd.print( target);
//    Serial.print(target);
//    Serial.print(" ");
//    Serial.print(pos);
//    Serial.println();
}

void setMotor(int dir, int pwmVal, int PWM, int in1, int in2){
  analogWrite(PWM,pwmVal);
  if(dir == 1){
    digitalWrite(7,engine_1);
    digitalWrite(6,engine_2);
  }
  else if(dir == -1){
    digitalWrite(7,!engine_1);
    digitalWrite(6,!engine_2);
  }
  else{
    digitalWrite(7,!engine_1);
    digitalWrite(6,engine_2);
  }
}

void readEncoder(){
  int b = digitalRead(ENCB);//INTERRUPCION ENCODER
  if(b > 0){
    posi++;
  }
  else{
    posi--;
  }
}
