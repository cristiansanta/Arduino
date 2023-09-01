const int leds[]={7,6,5,4,3,2};
volatile int i=3;

void setup() {Serial.begin(9600);
  for(int i=0;i<=5;i++){
  pinMode(leds[i], OUTPUT);
  }
  TCCR1A = 0;                        // El registro de control A queda todo en 0, pines OC1A y OC1B deshabilitados
  TCCR1B = 0;                        //limpia el registrador
  TCCR1B |= (1<<CS10)|(1 << CS12);   // configura prescaler para 1024: CS12 = 1 e CS10 = 1

  TCNT1 = 57724.5;//Inicia con 4 segundos  // inicia timer para desbordamiento 4 segundos
                                     // 65536-(16MHz/1024/(1Hz/4) - 1) = 3037 = 0xBDD
  
  TIMSK1 |= (1 << TOIE1);           // habilita la interrupcion del TIMER1
}

void loop() { 
//  for(int i=0;i<=5;i++){
//  digitalWrite(leds[i], HIGH);
//  delay(500);
//  }
//for(int i=5;i>=0;i--){
//  digitalWrite(leds[i], LOW);
//  delay(500);
//  }
 if(i==3){ digitalWrite(leds[2], HIGH);
  digitalWrite(leds[3], HIGH);

  if(i<=5){
  digitalWrite(leds[i], LOW);
  digitalWrite(leds[i+1], HIGH);
  digitalWrite(leds[5-i], LOW);
  digitalWrite(leds[4-i], HIGH);
      } 
  }
}
ISR(TIMER1_OVF_vect)                              //interrupcion del TIMER1
{
  TCNT1 = 57724.5;//----->500ms=0.5      // Renicia TIMER --  REACARGAR TIMER PARA DESBORDAR y queda ejecutandose con este nuevo valor de segundo asiganado
  i++;
  Serial.print(i); 
  digitalWrite(LED_BUILTIN, digitalRead(LED_BUILTIN) ^ 1); //invierte el estado do led
}
