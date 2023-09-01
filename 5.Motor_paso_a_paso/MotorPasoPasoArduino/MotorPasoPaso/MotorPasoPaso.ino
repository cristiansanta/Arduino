//*************************************************************//
//*************************************************************//
//****                                                    *****//
//**** MOTOR PASO A PASO CON ARDUINO                      *****//
//****                                                    *****//
//**** By: SERGIO ANDRES CASTAÑO GIRALDO                  *****//
//**** https://controlautomaticoeducacion.com/            *****//
//**** RIO DE JANEIRO - BRASIL - 2018                     *****//
//****                                                    *****//
//*************************************************************//
//*************************************************************//


//Declaración de los PULSADORES
byte PHorario = 2;     //Pulsador sentido horario
byte PAntiHorario = 3; //Pulsador sentido anti horario
byte PPasos = 4;       //Pulsador numero de pasos
byte PVel = 5;         //Pulsador velocidad


//Declaración de los PINES del Driver
byte IN1=8;  // 28BYJ48 In1
byte IN2=9;  // 28BYJ48 In2
byte IN3=10; // 28BYJ48 In3
byte IN4=11; // 28BYJ48 In4

int horario=1;

//*** Crear Matriz con los Pasos del Motor ***//

int paso=4; //Variable que indica el numero de pasos de las matrices
int Cpaso=0; //Contador de pasos

int vel[5]={5,10,30,100,500}; //Vector de velocidad
int Cvel=0; //Contador de Velocidad

int conf=1; //Variable que configura la secuencia de pasos

//secuencia 1 paso
const int UnPaso[4] = {      B1000, 
                             B0100, 
                             B0010, 
                             B0001 };
 
//secuencia 2 pasos
const int DosPasos[4] = {    B1100, 
                             B0110, 
                             B0011, 
                             B1001 };

// Secuencia a medio paso
byte const  MedioPaso[8] = { B1000,
                             B1100,
                             B0100, 
                             B0110, 
                             B0010, 
                             B0011, 
                             B0001, 
                             B1001 };

//Función que coloca en el puerto de salida los bits comenzando
// desde el pin ini hasta el pin fin
void puerto(int bits,int ini,int fin){
  for(int i=ini;i<=fin;i++)
  {
    digitalWrite(i,bitRead(bits,i-ini));
  }
}

void setup() {
  
  //Configura los 4 Pines de Pulsadores como ENTRADAS
  for(int i=2;i<=5;i++){
    pinMode(i,INPUT);
  }
  //Configura los 4 Pines digitales como SALIDAS
  for(int i=IN1;i<=IN4;i++){
    pinMode(i,OUTPUT);
  }

}

void loop() {

  //******************************************************************************//
  //***********    Pregunta por los Pulsadores   *********************************//
  //******************************************************************************//
  
  // Giro en Sentido Horario
  if(digitalRead(PHorario))  // Pregunta si pulsador horario fue presionado
  {
    delay(100); //Anti-Rebote
    horario=1;
    Cpaso=-1;
  }

  // Giro en Sentido Anti-Horario
  if(digitalRead(PAntiHorario))  // Pregunta si pulsador horario fue presionado
  {
    delay(100); //Anti-Rebote
    horario=0;
    Cpaso=paso;
  }

  // Cambio de la secuencia de pasos
  if(digitalRead(PPasos))  // Pregunta si pulsador horario fue presionado
  {
    delay(100); //Anti-Rebote
    while(digitalRead(PPasos)); //Espera hasta soltar el boton
    delay(100); //Anti-Rebote
    conf++;
    //Si ya paso por las 3 configuraciones reinicie
    if(conf>3)
      conf=1;
    if(horario==1)
      Cpaso=-1;
    else
      Cpaso=paso;

    puerto(B0000,IN1,IN4);
  }

  // Velocidad del Motor
  if(digitalRead(PVel))  // Pregunta si pulsador horario fue presionado
  {
    delay(100); //Anti-Rebote
    while(digitalRead(PVel)); //Espera hasta soltar el boton
    delay(100); //Anti-Rebote
    Cvel++;
    //Si ya paso por las 5 velocidades reinicie
    if(Cvel>4)
      Cvel=0;
  }

  //******************************************************************************//
  //***********    Logica de los contadores      *********************************//
  //******************************************************************************//
  if(horario==1)
  {
    Cpaso++;                        //Incremente la variable cont
    if(Cpaso>=paso)
       Cpaso=0;                          //Se pone Contador de pasos en cero 
  } 
  else{
    Cpaso--;                        //Decremente la variable cont
    if(Cpaso<0)
       Cpaso=paso-1;                  //Se pone Contador igual al paso
  }
  

  //******************************************************************************//
  //***********    Secuencia de Movimiento del Motor   ***************************//
  //******************************************************************************//

       switch(conf){
       case 1:
                puerto(UnPaso[Cpaso],IN1,IN4); //Envíe al puerto la información de la tabla
                paso=4;
                break;
       case 2:
                puerto(DosPasos[Cpaso],IN1,IN4); //Envíe al puerto la información de la tabla
                paso=4;
                break;
       case 3:
                puerto(MedioPaso[Cpaso],IN1,IN4); //Envíe al puerto la información de la tabla
                paso=8;
                break;
       }
        delay(vel[Cvel]);                      //Retardo de 100 milisegundos
  
}
