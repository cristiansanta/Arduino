byte D1= 2;        //a     //ORIGINAL
byte D2= 3;        //b
byte D3= 4;        //c
byte D4= 5;        //d
byte D5= 6;        //e
byte D6= 7;        //f
byte D7= 8;        //g
byte SwPLUS= 9;
byte SwPLUS0= 10;
long vel= 35;
int display_cont[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x67};
int cont=0;

//void convert(int bits, int ini, int fin);

void setup() {
for(int k=D1;k<=D7;k++)
{
  pinMode(k, OUTPUT);
}
  pinMode(SwPLUS, INPUT);
  pinMode(SwPLUS0, INPUT_PULLUP);
}

void loop() {

          conteo();
          convert(display_cont[cont],D1,D7); //------------------------------>Llamada de la funcion convert con los parametros
//          for(int k=D1;k<=D7;k++)   //------------------------------------------->Otra Opcion Sin Funcion Que Funciona
//          {
//            digitalWrite(k,bitRead(display_cont[cont],k-D1));
//          }
}

void conteo()
{
  if(digitalRead(SwPLUS))
          { delay(vel);
            while(digitalRead(SwPLUS));   //--------->WHILE Anti-rebote para elementos mecánicos como pulsadores, switches, relés, etc.
            delay(vel);
            cont++;
          }
          if(!digitalRead(SwPLUS0))
          { delay(vel);
            while(!digitalRead(SwPLUS0)); //--------->WHILE Anti-rebote para elementos mecánicos como pulsadores, switches, relés, etc.
            delay(vel);
            cont--;
          }
          if(cont>9)
          {
            cont=0;
          }
          if(cont<0)
          {
            cont=9;
          }
}
void convert(int bits, int ini, int fin)
{
  for(int i=ini; i<=fin; i++)
  {
    digitalWrite(i, bitRead(bits,i-ini)); //bits=Número binario; i-ini=posicion del numero binario bitRead=toda esta funcion entrega el bit del numero binario lo desglosa
  }
}
