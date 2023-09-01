#include <Servo.h>//////////////////////CONTROL SERVOMOTOR CON MENÚ

//Variables Globales
bool menu=true;
int degree=0;
String words;
Servo servo77;// Objects are created "Servos"

void setup() {
  Serial.begin(9600);
  Serial.println("+++++++Control-Servo en Grados++++++++++++");//
  servo77.attach(3,600,2400);//3=pin -- 600uSeconds=Pulso mínimo --- 2400uSeconds=Pulso máximo
  servo77.write(0);//Posicion inicial o angulo cero (0°)
}

void loop() {

       if(menu==true)
       {
        Serial.println("------------------- CURSO ARDUINO - CONTROL SERVOMOTOR -----------------");
        Serial.println("1) Posicion Inicial");
        Serial.println("2) Mover 65 grados");
        Serial.println("3) Mover 90 grados");
        Serial.println("4) Mover 125 grados");
        Serial.println("5) Mover 180 grados");
        menu=false;
       }
  
  while(Serial.available())//Read the value sent by the Serial Port
  {delay(25);
   char c = Serial.read();
   words+=c;
  }
  degree=words.toInt();//convert character string to integers
if(degree != 0)
{  
  if(degree>=1 && degree<=5)
  {
    switch(degree){
      
      case 1: delay(25);
              servo77.write(0);
              clearscreen();
              Serial.println(" 0 GRADOS(posicion inicial)");
                            
              while(servo77.read()<0){
                  Serial.println("Desplazando...");
                  }
              break;
              
      case 2: delay(25);
              servo77.write(65);
              clearscreen();
              Serial.println(" 65 GRADOS");
              while(servo77.read()<65){
                  Serial.println("Desplazando...");
                  }
              break;
              
      case 3: delay(25);
              servo77.write(90);
              clearscreen();
              Serial.println(" 90 GRADOS");
              while(servo77.read()<90){
                  Serial.println("Desplazando...");
                  }
              break;
              
      case 4: delay(25);
              servo77.write(125);
              clearscreen();
              Serial.println(" 125 GRADOS");
              while(servo77.read()<125){
                  Serial.println("Desplazando...");
                  }
              break;
              
      case 5: delay(25);
              servo77.write(180);
              clearscreen();
              Serial.println(" 180 GRADOS");
              while(servo77.read()<180){
                  Serial.println("Desplazando...");
                  }
              break;
    }
  }else{Serial.println("OPCION INVALIDA");}
  menu=true;
  degree=0;
}
  words="";
}
//Función para limpiar TERMINAL
void clearscreen() { 
    for(int i=0;i<50;i++) { 
     Serial.println("\n\n\n\n\n\n\n\n\n\n\n\n\n"); 
    } 
} 
/*
#include <Servo.h>

//Variables Globales
int degree=0;
String words;
Servo servo77;// Objects are created "Servos"

void setup() {
  Serial.begin(9600);
  Serial.println("Control-Servo");
  servo77.attach(3,600,2400);//3=pin -- 600uSeconds=Pulso mínimo --- 2400uSeconds=Pulso máximo
  servo77.write(0);//Posicion inicial o angulo cero (0°)
}

void loop() {
  while(Serial.available())//Read the value sent by the Serial Port
  {delay(150);
   char c = Serial.read();
   words+=c;
  }
if(words.length() > 0)
{
  degree=words.toInt();//convert character string to integers
  Serial.print(degree);
  Serial.println(" GRADOS");
  Serial.print(" ");
  delay(5);
  servo77.write(degree);
  while(servo77.read()<degree)
  {
    Serial.println("Desplazando...");
  }
}
  words="";
}
*/
