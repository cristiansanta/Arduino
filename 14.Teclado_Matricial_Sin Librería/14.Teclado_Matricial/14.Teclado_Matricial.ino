#include <LiquidCrystal.h>;
LiquidCrystal lcd(14,13,12,11,10,9);
int filas[4]={5,4,3,2};
int colm[3]={6,7,8};
char teclas[4][3]={{'1','2','3'},{'4','5','6'},{'7','8','9'},{'*','0','#'}};
byte c=0,f=0;

bool readkeypad()  //Función
{
  bool retorna=false;
  // Barrido de columnas
  for(byte nC=0;nC<=2;nC++)
  {   // Poner columna a LOW
    digitalWrite(colm[nC], LOW);
    // Barrer todas las filas comprobando pulsaciones
    for(byte nF=0;nF<=3;nF++)
    {  if(digitalRead(filas[nF])==LOW)
      {
        f=nF;
        c=nC;
        while(digitalRead(filas[nF])==LOW);
        retorna=true;
      }
    }
    // Devolver la columna a alta impedancia
    digitalWrite(colm[nC], HIGH);
  }
  return retorna;
}

void setup() {
Serial.begin(9600);
lcd.begin(16,2);
for(int nF=0;nF<=3;nF++)
{
    pinMode(filas[nF], INPUT_PULLUP);
}
for(int nC=0;nC<=2;nC++)
{
  pinMode(colm[nC], OUTPUT);
  digitalWrite(colm[nC], HIGH);
}
}

void loop() {
  if(readkeypad())
  {
       lcd.home();
       lcd.print(teclas[f][c]);
       Serial.print(teclas[f][c]);
       Serial.print(" ");
  }
  delay(10);
}
