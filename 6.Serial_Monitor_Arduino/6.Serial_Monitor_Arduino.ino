byte pin = 6; 
int CA[10]={0x40,0x79,0x24,0x30,0x19,0x12,0x02,0x78,0x00,0x18};
byte g=7;
byte h=8;
byte i=9;
byte j=10;
byte k=11;
byte l=12;
byte m=13;
int C=0;

void puerto(int bits, int ini, int fin){
  for(int i=ini;i<=fin;i++)
  {
    digitalWrite(i, bitRead(bits,i-ini));
  }    
}

void setup() {
Serial.begin(9600);
pinMode(pin, OUTPUT);
for(int i=g;i<=m;i++)
{
  pinMode(i, OUTPUT);
}
}

void loop() {
  puerto(CA[C-48],g,m);
       if(Serial.available())//Detecta si se escribe en el serial monitor
       {
        C=Serial.read();
        Serial.print(C);
        if(C=='E')
        {
          digitalWrite(pin, HIGH);
        }
        if(C=='A'){
           digitalWrite(pin, LOW);}
        if(C>='0' && C<='9')
        {
          puerto(CA[C-48],g,m);
        }
       }
}

//---------------------------------------------> TABULAR
/* Tutorial 3: Puerto Serial
En este tutorial, vamos a leer y escribir datos en el puerto serial.
 
  Ejemplo 1º: Lectura de variables de programa a traves del puerto serial.
*/
 /*
int LED = 10;     //Asociamos el pin 10 a la salida del LED
int NIVEL_TENSION = 0;  //Asociamos el pin 0 a la entrada de señal
int VALOR = 0;    //Creamos una variable y le asignamos el valor "0" como partida
 
void setup(){
  Serial.begin(9600);
  pinMode(LED, OUTPUT);  //Establece el el pin al que conectamos el LED como salida (no es necesario)
  pinMode(NIVEL_TENSION, INPUT);  //Establece el el pin por el que entrará la señal analógica (no es necesario)
}
   
 
void loop(){
 VALOR = analogRead(NIVEL_TENSION);  //Asignamos a la variable "VALOR" el nivel de tensión leido
 Serial.print("Valor 10 bit's: ");   //Imprime el texto que esta entre las comillas
 Serial.print(VALOR);                //Imprime el la variable "VALOR" (10 bit's)
 Serial.print("\t");                 //Introduce una tabulación
 VALOR = VALOR/4;  //Al leer un valor analogico, este tiene 10 bit's, va de 0 a 1023, por lo que debemos adaptarlo al rango de 0 a 255
                   //(una manera sencilla es dividiendo entre 4)
 analogWrite (LED, VALOR);
 Serial.print("Valor 8 bit's: ");    //Imprime el texto que esta entre las comillas
 Serial.println(VALOR);              //Imprime el la variable "VALOR" (8 bit's)
 delay(1000);
}
*/