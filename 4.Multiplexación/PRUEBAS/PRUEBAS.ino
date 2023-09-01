int CC[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x67};
int pin[]={2,3,4,5,6,7,8};
byte t4=12;
byte t3=11;
byte t2=10;
byte t1=9;

void setup() {Serial.begin(9600);
  // put your setup code here, to run once:
  for(int k=2;k<=8;k++)
  {
    pinMode(k, OUTPUT);
  }
  for(int i=9;i<=12;i++)
  {
    pinMode(i, OUTPUT);
  }

}

void loop() {
int contador=0;

  while(contador<=9){
    
    digitalWrite(12, HIGH);
    delay(1);
    digitalWrite(11, LOW);
    delay(1);
    digitalWrite(10, LOW);
    delay(1);
    digitalWrite(9, LOW);
    convert(CC[contador],2,8);
    delay(1);
    
    contador++;
    Serial.print(contador);
    delay(300);
    
  }  
}

void convert(int bits, int ini, int fin)
{
  for(int i=ini; i<=fin; i++)
  {
    digitalWrite(i, bitRead(bits,i-ini)); //bits=Número binario; i-ini=posicion del numero binario bitRead=toda esta funcion entrega el bit del numero binario lo desglosa
  }
}
