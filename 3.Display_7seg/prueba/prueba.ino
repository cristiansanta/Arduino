byte D1= 2;        //a // FUNCIONANDO BIEN
byte D2= 3;        //b
byte D3= 4;        //c
byte D4= 5;        //d
byte D5= 6;        //e
byte D6= 7;        //f
byte D7= 8;        //g
byte t1= 9;    //TRANSISTORES
byte t2= 10;
#define SwPLUS 11    //PULSADORES
#define SwPLUS0 12
long vel= 35;
int display_cont[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x67};
long cont=0;
bool n=false;

//void convert(int bits, int ini, int fin);

void setup() {
for(int k=D1;k<=10;k++)
{
  pinMode(k, OUTPUT);
}
  pinMode(SwPLUS, INPUT);
  pinMode(SwPLUS0, INPUT_PULLUP);
  Serial.begin(9600);
}

void loop() {
          if(digitalRead(SwPLUS))
          { delay(vel);
            while(digitalRead(SwPLUS));   //--------->WHILE Anti-rebote para elementos mecánicos como pulsadores, switches, relés, etc.
            delay(vel); 
            n=true;         
            cont++;
          }
          if(!digitalRead(SwPLUS0))
          { delay(vel);
            while(!digitalRead(SwPLUS0)); //--------->WHILE Anti-rebote para elementos mecánicos como pulsadores, switches, relés, etc.
            delay(vel);
            mostrar();
            n=true;
            cont--;
          }
          if(n==1)
            {
              mostrar();
            }
          if(cont==0)
          {
            mostrar();
          }
          if(cont>99)
          {
            cont=0;
          }
          if(cont<0)
          {
            cont=99;
          }

          

          
//          for(int k=D1;k<=D7;k++)   //------------------------------------------->Otra Opcion Sin Funcion Que Funciona
//          {
//            digitalWrite(k,bitRead(display_cont[cont],k-D1));
//          }
}

void mostrar()
{
  int HX[2];
              HX[0]=cont/10;//pin 9 decenas
              HX[1]=cont-HX[0]*10;//pin 10 unidades
              
            for(int i=t1;i<=t2;i++)
            {
               convert(display_cont[HX[i-t1]],D1,D7); //------------------------------>Llamada de la funcion convert con los parametros
//               Serial.print(HX[i-t1]);
//              delay(333);
               digitalWrite(i, HIGH);
               delay(1);
               digitalWrite(i, LOW);
            }
}

void convert(int bits, int ini, int fin)
{
  for(int i=ini; i<=fin; i++)
  {
    digitalWrite(i, bitRead(bits,i-ini)); //bits=Número binario; i-ini=posicion del numero binario bitRead=toda esta funcion entrega el bit del numero binario lo desglosa
  }
}
