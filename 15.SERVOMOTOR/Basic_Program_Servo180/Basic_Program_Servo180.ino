#include "Servo.h"//Libreria
Servo santa;//Se crea objeto para el Servo


void setup()
{
  santa.attach(5); //designar Pin para control servo con pwm
}

void loop()
{
  santa.write(0);//escribir el angulo a mover a la salida
  delay(1500);
  santa.write(90);
  delay(1500);
  santa.write(180);
  delay(1500);
}
