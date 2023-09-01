const byte A=6;   //SALIDAS DRIVER
const byte B=7;
const byte C=8;
const byte D=9;

  //PULSADORES
byte P1=2;//GIRO HORARIO
byte P2=3;//GIRO ANTI-HORARIO
byte P3=4;//SECUENCIA MOVIMIENTO
byte P4=5;//VELOCIDAD MOTOR

byte sentido=1;
byte paso=4;
int cont_paso=-1;//ESTE ERA EL ERROR Porque Lo tenia declarado con byte y el byte tiene un rango muy limitado
byte conff=2;

int Mvel[5]={25,50,100,250,500};
int vel=2;


const int unpaso[4]={B1000,B0100,B0010,B0001};//B1000-->DCBA-->D=1,C=0,B=0,A=0. B1000=bitsss A=ini - D=fin
const int Dospasos[4]={B1100,B0110,B0011,B1001};
const int mediopaso[8]={B1000,
                    B1100,
                    B0100,
                    B0110,
                    B0010,
                    B0011,
                    B0001,
                    B1001};

void bits(int bitsss, int ini, int fin )//B1000-->DCBA-->D=1,C=0,B=0,A=0. B1000=bitsss  D=1=fin - A=0=ini
{
  for(int i=ini;i<=fin;i++)    // bitsss=unpaso[3]=B0001 al vector de cada secuencia segun la eleccion
  {
    digitalWrite(i, bitRead(bitsss,i-ini));//ESCRIBO EN LAS SALIDAS OUTPUT los bits entregados por dicha funcion.-----SACA LOS BITS POR CADA PIN DEL ARDUINO
  }
}

void setup() {
     for(int k=2;k<=5;k++)
     {
         pinMode(k, INPUT_PULLUP);
     }
     for(int i=6;i<=9;i++)//------------> PINES utilizados por la funcion bitRead
     {
        pinMode(i, OUTPUT);
     }
   Serial.begin(9600);
}

void loop() {
  if(!digitalRead(P1))//SENTIDO HORARIO
  { delay(35);
    sentido=1;
    Serial.print(sentido);
    cont_paso=-1;
  }
  if(!digitalRead(P2))//SENTIDO ANTIHORARIO
  { delay(35);
    sentido=0;
    Serial.print(sentido);
    cont_paso=paso;
  }
  if(!digitalRead(P3))//SECUENCIA MOVIMIENTO
  {  delay(35);
     while(!digitalRead(P3));
     delay(35);
     conff++;
     if(conff>3)
     conff=1;   
//     if(sentido==1)
//         cont_paso=-1;
//     else
//         cont_paso=paso;
//     bits(B0000,A,D);   //   ----------------> Llama funcion bitRead
  }
  if(!digitalRead(P4))//VELOCIDAD MOTOR
  {delay(35);
     while(!digitalRead(P4));
     delay(35);    
     vel++;
     Serial.print(vel);
     if(vel>4)
     vel=0;
  }
  if(sentido==1)//LOGICA CONTADORES //Por defecto inicia en sentido horario
  {
    cont_paso++;//POR DEFECTO INICIA EN -1 Y AL AUMENTAR 1 QUEDA EN LA POSICION CERO DEL VECTOR DE LA SECUENCIA
    if(cont_paso>=paso)
    cont_paso=0;
  }
  else{
    cont_paso--;
    if(cont_paso<0)
    cont_paso=paso-1;
  }
Serial.print(conff);//Por defecto inicia la configuración de movimiento en 2
  switch (conff)
  {
    case 1:  bits(unpaso[cont_paso],A,D);//bitsss= unpaso[cont_paso]--------->ESTO SE ENVIA A LA FUNCION bitRead Y SACA LOS BITS POR CADA PIN DEL ARDUINO
             
             Serial.print(" Un paso ");
    break;
    
    case 2:  bits(Dospasos[cont_paso],A,D);//bitsss= Dospasos[cont_paso]--------->ESTO SE ENVIA A LA FUNCION bitRead Y SACA LOS BITS POR CADA PIN DEL ARDUINO
             
             Serial.print(" Dos pasos ");
    break;
    
    case 3:  bits(mediopaso[cont_paso],A,D);//bitsss= mediopaso[cont_paso]--------->ESTO SE ENVIA A LA FUNCION bitRead Y SACA LOS BITS POR CADA PIN DEL ARDUINO
             paso=8;
             Serial.print(" Medio paso ");
    break;
  }
  delay(Mvel[vel]);
}
