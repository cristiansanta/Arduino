#include <LiquidCrystal.h>
LiquidCrystal lcd(14, 13, 12, 11, 10, 9); //A0=14

int DT = 2;
int CLK = 3;

int Pos = 0; 
int State;
int LastState;  

const float pi = 3.14;
const float R = 3.25;
const int N = 40;

float distance = 0;

int EN1 = 5;//Inyectar PWM para controlar velocidad motor
int engine_1 = HIGH, engine_2 = LOW;
byte PWM=75;//VELOCIDAD MOTOR


void setup() { 
  pinMode (DT ,INPUT_PULLUP);
  pinMode (CLK ,INPUT_PULLUP);
  pinMode(7, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(EN1, OUTPUT);
  
  lcd.begin(16, 2);
  lcd.print("MEASURNING WHEEL");
  
  LastState = digitalRead(DT);    
} 

void loop(){
  digitalWrite(7, engine_1);
  digitalWrite(6, engine_2);
  analogWrite(EN1, PWM);
  
  State = digitalRead(DT);
   if (State != LastState){     
     if (digitalRead(CLK) != State) { 
       Pos ++;
     } 
     
     else {
       Pos --;
     }
   } 
  distance = ((2*pi*R)/N) * Pos ;
  lcd.setCursor(0, 1);
  lcd.print( distance);
  lcd.setCursor(5, 1);
  lcd.print("cm  ");
   
  LastState = State;
 }
