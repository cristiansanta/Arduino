//Declaraciones
byte L1= 2;
byte L2= 3;
byte L3= 4;
byte L4= 5;
byte L5= 6;
byte L6= 7;

long vel=250;

void setup() {
  // put your setup code here, to run once:
  for(int i=L1;i<=L6;i++)
  {
    pinMode(i, OUTPUT);
  }
}

void loop() {
  // put your main code here, to run repeatedly:
    for(int i=2;i<=7;i++)  //CICLO para iniciar prendiendo
    {
      digitalWrite(i, 1);
      delay(vel);
    }
  int i=7;       //CICLO WHILE para devolverse en el apagado
  while(i>=2)
  {
    digitalWrite(i, LOW);
    delay(vel);
    i--;
  }
   //Inicia prendiendo los leds de medio
    digitalWrite(L3, HIGH);
    digitalWrite(L4, HIGH);
    delay(1000);

 for(int i=5;i<=7;i++)
 {
    digitalWrite(i, LOW);
    digitalWrite(i+1, HIGH);
    digitalWrite(9-i, LOW);
    digitalWrite(8-i, HIGH);
    delay(vel);
 }
}
