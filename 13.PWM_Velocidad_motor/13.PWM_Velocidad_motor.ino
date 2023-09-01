const int pot=A0;
#define Motor 5

void setup() {
  pinMode(Motor, OUTPUT);
}

void loop() {
  analogRead(pot);
  analogWrite(Motor, analogRead(pot)/4);
}
//analogWrite(pwma, 255);
/*

//ROBOT_SUMO 3KG
//CORPORACION UNIVERSITARIA AUTONOMA DEL CAUCA

#include <LiquidCrystal_I2C.h>
#include <Wire.h>

LiquidCrystal_I2C lcd(0x3f,16,2); // Constructor for LCD, (Address of LCD, NoOfColumns,NoOfRows)

#define pwma 3//izquierdo
#define pwmb 5//derecho
#define a1   2
#define a2   4
#define b1   6
#define b2   7
#define led 53 //conteo segundos reglamentarios

const int Trigger = 22;   //Pin digital 2 para el Trigger del sensor    ---> derecho
const int Echo = 24;   //Pin digital 3 para el Echo del sensor
const int Trigger_1 = 28;   //Pin digital 2 para el Trigger del sensor  ---> izquierdo
const int Echo_1 = 30;   //Pin digital 3 para el Echo del sensor
const int Trigger_2 = 34;   //Pin digital 2 para el Trigger del sensor  ---> adelante 1
const int Echo_2 = 36;   //Pin digital 3 para el Echo del sensor
const int Trigger_3 = 43;   //Pin digital 2 para el Trigger del sensor  ---> adelante 2
const int Echo_3 = 45;   //Pin digital 3 para el Echo del sensor

int busquedad = 0;
void setup() {
  Serial.begin(9600);//iniciailzamos la comunicación
   lcd.init();             // initialize the lcd
   lcd.backlight();         // backlight of lcd 
   lcd.clear();
  pinMode(a1, OUTPUT);
  pinMode(a2, OUTPUT);
  pinMode(pwma, OUTPUT);
  pinMode(b1, OUTPUT);
  pinMode(b2, OUTPUT);
  pinMode(pwmb, OUTPUT);
   
  pinMode(Trigger, OUTPUT); //pin como salida
  pinMode(Echo, INPUT);  //pin como entrada
  digitalWrite(Trigger, LOW);//Inicializamos el pin con 0

  pinMode(Trigger_1, OUTPUT); //pin como salida
  pinMode(Echo_1, INPUT);  //pin como entrada
  digitalWrite(Trigger_1, LOW);//Inicializamos el pin con 0

   pinMode(Trigger_2, OUTPUT); //pin como salida
  pinMode(Echo_2, INPUT);  //pin como entrada
  digitalWrite(Trigger_2, LOW);//Inicializamos el pin con 0

   pinMode(Trigger_3, OUTPUT); //pin como salida
  pinMode(Echo_3, INPUT);  //pin como entrada
  digitalWrite(Trigger_3, LOW);//Inicializamos el pin con 0

  pinMode(8, INPUT);//sensores de linea en pines digitales con funcion booleana
  pinMode(9, INPUT);
  pinMode(10, INPUT);
  pinMode(11, INPUT);

  pinMode(led, OUTPUT); //led indicador tiempo reglamentario de 5 segundos

//  analogWrite(pwma, 150); //velocidad de motores
//  analogWrite(pwmb, 150);
   tiempo();
}

void loop(){  
  boolean adelante_izq = digitalRead(9); //Sensores de piso
  boolean adelante_der = digitalRead(10);
  boolean atras_izq = digitalRead(11);
  boolean atras_der = digitalRead(12);

  long t; //timepo que demora en llegar el eco
  long d; //distancia en centimetros
  long t_1; //timepo que demora en llegar el eco
  long d_1; //distancia en centimetros
  long t_2; //timepo que demora en llegar el eco
  long d_2; //distancia en centimetros
  long t_3; //timepo que demora en llegar el eco
  long d_3; //distancia en centimetros

  if(adelante_izq == LOW)
{
          lcd.clear();
          lcd.setCursor(0,1);
          lcd.print("adelante_izq");
          delay(60);
  Serial.println("adelante_izq");
         parar();
         delay(60);
         back();
         delay(400);
         right();
        // delay(800);  
}
else if(adelante_der == LOW)
{
          lcd.clear();
          lcd.setCursor(0,1);
          lcd.print("adelante_der");
          delay(60);
  Serial.println("adelante_der");  
         parar();
         delay(60);
         back();
         delay(400);
         left(); 
}
else if(atras_izq == LOW)
{
          lcd.clear();
          lcd.setCursor(0,1);
          lcd.print("atras_izq");
          delay(60);
  Serial.println("atras_izq");  
         parar();
         delay(60);
         forward();
         delay(400);
         right();  
}
else if(atras_der == LOW)
{
          lcd.clear();
          lcd.setCursor(0,1);
          lcd.print("atras_der");
          delay(60);
  Serial.println("atras_der");  
         parar();
         delay(60);
         forward();
         delay(400);
         left();
}
else{
  digitalWrite(Trigger, LOW);
  delayMicroseconds(2);    
  digitalWrite(Trigger, HIGH);
  delayMicroseconds(10);          //Enviamos un pulso de 10us
  digitalWrite(Trigger, LOW);
  t = pulseIn(Echo, HIGH); //obtenemos el ancho del pulso
  d = t/59;             //escalamos el tiempo a una distancia en cm

  digitalWrite(Trigger_1, LOW);
  delayMicroseconds(2);      
  digitalWrite(Trigger_1, HIGH);
  delayMicroseconds(10);          //Enviamos un pulso de 10us
  digitalWrite(Trigger_1, LOW);
  t_1 = pulseIn(Echo_1, HIGH); //obtenemos el ancho del pulso
  d_1 = t_1/59;        

  digitalWrite(Trigger_2, LOW);
  delayMicroseconds(2);      
  digitalWrite(Trigger_2, HIGH);
  delayMicroseconds(10);          //Enviamos un pulso de 10us
  digitalWrite(Trigger_2, LOW);
  t_2 = pulseIn(Echo_2, HIGH); //obtenemos el ancho del pulso
  d_2 = t_2/59;       

  digitalWrite(Trigger_3, LOW);
  delayMicroseconds(2);      
  digitalWrite(Trigger_3, HIGH);
  delayMicroseconds(10);          //Enviamos un pulso de 10us
  digitalWrite(Trigger_3, LOW);
  t_3 = pulseIn(Echo_3, HIGH); //obtenemos el ancho del pulso
  d_3 = t_3/59;       
  
  if(d < 10)
  {
          lcd.clear();
          lcd.setCursor(0,1);
          lcd.print("DERECHA");
          delay(60);
  Serial.println("DERECHA");
         right();
         delay(500);
  }
  else if(d_1 < 10)
  {
          lcd.clear();
          lcd.setCursor(0,1);
          lcd.print("IZQUIERDA");
          delay(60);
    Serial.println("IZQUIERDA");  
          left();
          delay(500);
  }
   else if(d_2 < 10 || d_3 < 10)
  {
          lcd.clear();
          lcd.setCursor(0,1);
          lcd.print("ADELANTE");
          delay(60);
    Serial.println("ADELANTE");  
         forward();
         delay(500); 
  }
  
  else{
         if (busquedad < 15) { // Avanza 15 ciclos (alrededor de 20 ciclos en un segundo)
          lcd.clear();
          lcd.setCursor(0,1);
          lcd.print("search right");
          delay(60);
        Serial.println("busqueda a la derecha"); 
          right();
          delay(500);
      }
      else if (busquedad <= 20) { // Girar a la derecha 5 ciclos
          lcd.clear();
          lcd.setCursor(0,1);
          lcd.print("search forward");
          delay(60);
        Serial.println("busqueda hacia adelante");
          forward();
          delay(500);
      }
      if (busquedad < 20) {
        busquedad += 1;    
      }
      else if (busquedad == 20) {
        busquedad = 0;
      }      
  }
 }
 delay(50);// Esto + el tiempo que lleva lo anterior es un ciclo.
}

 ////10 atras_izq, 11 atras_der, 8 adelante_izq, 9 adelante_der

 
void forward()
{
  digitalWrite(a1,LOW);  //adelante
  digitalWrite(a2,HIGH);
  analogWrite(pwma, 255);
  digitalWrite(b1,HIGH);
  digitalWrite(b2,LOW);
  analogWrite(pwmb, 255);
}

void back()
{
  digitalWrite(a1,HIGH);  //atras
  digitalWrite(a2,LOW);
   analogWrite(pwma, 255);
  digitalWrite(b1,LOW);
  digitalWrite(b2,HIGH);
   analogWrite(pwmb, 255);
}

void left()
{
  digitalWrite(a1, HIGH);  //izquierda
  digitalWrite(a2, LOW);
   analogWrite(pwma, 120);
  digitalWrite(b1, HIGH);
  digitalWrite(b2, LOW);
   analogWrite(pwmb, 120);
}

void right()
{
  digitalWrite(a1, LOW);  //derecha
  digitalWrite(a2, HIGH);
   analogWrite(pwma, 120);
  digitalWrite(b1, LOW);
  digitalWrite(b2, HIGH);
   analogWrite(pwmb, 120);
}

void parar()
{
  digitalWrite(a1, LOW);  //pare
  digitalWrite(a2, LOW);
  digitalWrite(b1, LOW);
  digitalWrite(b2, LOW);
}

void tiempo()    //funcion para tiempo reglamentario
{
  digitalWrite(led, HIGH);
  delay(500);
  digitalWrite(led, LOW);
  delay(500);
  digitalWrite(led, HIGH);
  delay(500);
  digitalWrite(led, LOW);
  delay(500);
  digitalWrite(led, HIGH);
  delay(500);
  digitalWrite(led, LOW);
  delay(500);
  digitalWrite(led, HIGH);
  delay(500);
  digitalWrite(led, LOW);
  delay(500);
  digitalWrite(led, HIGH);
  delay(500);
  digitalWrite(led, LOW);
  delay(500);
}

*/
