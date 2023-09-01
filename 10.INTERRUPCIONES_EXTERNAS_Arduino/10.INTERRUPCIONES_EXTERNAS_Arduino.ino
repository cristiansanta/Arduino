volatile int cont=0;
unsigned long mytime=0;
const byte led=8;
int save=0;
void setup() {
  Serial.begin(9600);
//  pinMode(3, INPUT_PULLUP);//Si se quiere input_pullup se debe declarar en la configuracion y si es entrada normal osea INPUT solo se pone el pin en la interrupcion
  attachInterrupt(digitalPinToInterrupt(3), cuenta, RISING);//digitalPinToInterrupt(3)==1;  - -  digitalPinToInterrupt(2)==0;
}

void loop() {
  digitalWrite(led, HIGH);
  delay(1000);
  digitalWrite(led, LOW);
  delay(1000);
///////////////////////////Serial.println(cont);
       
}

void cuenta()//COMO CONLUSION SE DICE QUE LAS INTERRUPCIONES SON INDEPENDIENTES LO QUE QUIERE DE DECIR QUE NO NECESITAN DE LA FUNCION PRINCIPAL *VOID LOOP*
{

   //cont++;
  
  if(millis() - mytime > 150)
  { 
    cont++;
    mytime=millis();
//    Serial.print(mytime);
//    Serial.print(" ");
if(save != cont)
       {save=cont;
        Serial.print("Cuenta: ");
        Serial.println(cont);
       }
  }
}
