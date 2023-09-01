#include <Servo.h>

int dir=0, menu=1,OP=0;
char c='\0';
String words;

Servo Santa;

void setup() {
  Serial.begin(9600);
  Serial.print("CURSO ARUDINO");
  Santa.attach(5);
  Santa.write(90);//POSICIÓN INICIAL EN angulo CERO (0)
}

void loop() {
      if(menu==1)
      {
         Serial.print("----------- DIGITE UNA OPCION: --------------");
         Serial.print("1. Sentido horario");
         Serial.print("2. Sentido Anti-Horario");
         Serial.print("3. Detener motor");
         menu=0;
      }
   while(Serial.available())
   { delay(500);
     c=Serial.read();
     words = words +c;//acumulador va aumentando en una cantidad variable.
   }
   
     OP=words.toInt();
   if(/*words.length()*/OP > 0)
   { if(OP>=1 && OP<=3){
      switch(OP)
      {case 1:
              Santa.write(0);
              Serial.println("Sentido Horario");
              return 0;
       case 2:
              Santa.write(180);
              Serial.println("Sentido Anti-Horario");
              return 0;
       case 3:
              Santa.write(90);
              Serial.println("Motor en STOP");
              return 0;
      }
   } else{ Serial.println("OPCIÓN INVALIDA!!!");
        }
        menu=1;
         OP=0;
   }
   words = "";
}
