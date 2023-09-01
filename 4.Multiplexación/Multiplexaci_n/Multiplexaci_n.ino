//int pines[20]={2,3,4,5,6,7,8,9,10,11,12}; //------------>NO SIRVE DECLARARLOS ASI para el 7 segmentos
byte a=2;
byte b=3;
byte c=4;
byte d=5;
byte e=6;
byte f=7;
byte g=8;
//Transistores
byte e0=9;
byte e1=10;
byte e2=11;
byte e3=12;
int CC[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x67};
long contador=0, conta_retardo=0;

void setup() {
  for(int k=2;k<=12;k++)
  {
    pinMode(k, OUTPUT);
  }
  Serial.begin(9600);
}

void loop() {
  
           contador=0; // ----------> Contador Principal
           while(contador<9999)
           { 
              temporizar();//Retardo de un segundo y aumenta
              contador++;
           }
}
void temporizar()//Sirve como retardo de un segundo para aumentar el contador principal
{
  conta_retardo=50;
  while(conta_retardo>0)
  {
    mostrar();//Se ejecuta cada 5 milisegundos y cuando el decremento llegue a cero se sale y aumentará una unidad el contador principal
    conta_retardo--;
  }
}

void mostrar()
{
  int dig[4];
  
      
dig[0]=contador/1000;
//   //Dígito Centena
   dig[1]=(contador-dig[0]*1000)/100;
   //Dígito Decena
   dig[2]=(contador-dig[0]*1000-dig[1]*100)/10;
//   //Dígito Unidad
   dig[3]=(contador-dig[0]*1000-dig[1]*100-dig[2]*10);
      
   for(int i=9;i<=12;i++)
   {
        puerto(CC[dig[i-9]],2,8);
        Serial.print(CC[dig[i-9]]);
        digitalWrite(i, HIGH);
        delay(1);
        digitalWrite(i, LOW);
      
   }
}
void puerto(int bits, int ini, int fin)
{
  for(int k=2;k<=8;k++)
  {
    digitalWrite(k, bitRead(bits,k-2));//Envia un bit por cada pin del arduino para activar el 7 segmentos
  }
}
