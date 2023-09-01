#include <LiquidCrystal.h>
#include <Wire.h>
#include <Keypad.h>
#include <EEPROM.h>
LiquidCrystal lcd(54,13,12,11,10,9);   //A0=54
//#include <LiquidCrystal_I2C.h>
//LiquidCrystal_I2C lcd(0x3F,16,2);
//Variables Teclado
char key1[4][4]={{'1','2','3','A'},{'4','5','6','B'},{'7','8','9','C'},{'*','0','#','D'}};
byte fila[4]={2,3,4,5};//SALIDA
byte col[4]={21,20,19,18};//INPUT

//Otras Variables 
const byte filas = 4;
const byte cols = 4;
const int POT=A2;
int currentPW=1028,PW_input,valPot;//PW_input Al ser una variable entera tiene 2 bytes
float volts;
char Key;

Keypad teclado = Keypad( makeKeymap(key1), fila, col, filas, cols);

void setup() {
  lcd.begin(16,2);
//  lcd.init();
//  lcd.backlight();
  Serial.begin(9600);
  lcd.home();
  lcd.print("A.Guarda B.Muestra ");
  lcd.setCursor(0,1);
  lcd.print("C.Cambia D.Anula ");
  delay(500);
  lcd.clear();
  teclado.setHoldTime(1000);           ///REVISAR
  EEPROM.get(0, PW_input );
  if(PW_input!=currentPW && PW_input>0)
  {
    currentPW = PW_input;
  }  //RECUPERAR CONTRASEÑA
//    lcd.print("PASSWORD EEPROM: ");
//    lcd.setCursor(0,3);
//    lcd.print(currentPW);
//    delay(5000);
}

int password()
{ bool flag=false; //VARIABLES LOCALES
  int pass,m=0;
   String contrase;
   lcd.setCursor(0,1);                     ///REVISAR PONER DENTRO DEL CICLO
   while(m<4)
   {
     Key=teclado.waitForKey();            ///.waitForKey() != .getKey()porque el primero paraliza el codigo getkey NO
     if(Key>='0' && Key<='9')
     { lcd.print('*');
     contrase = contrase + Key;//CONCATENAR
     m++;
     }
     if(Key=='D')//-------------------------------------------------->  ///ANULAR ACCION
     { m=4;
       flag=true;
     }
     if(flag==true)
            {
             lcd.clear();
             lcd.home();
             lcd.print("ACCION ANULADA");
             flag=false;
             PW_input=currentPW;
             delay(1500);
             lcd.clear();
             break;
            }
   }
   if(contrase.length()>0)
   {  pass=contrase.toInt();
   }
   else{
       pass=0;
   }
   return pass;
}

void loop() {
     char OP; bool flag1=false;
     int i,j;
     float VEE[4];//Vector con 4 posiciones para almacenar los 4 voltajes en la EEPROM
     
     valPot=analogRead(POT);
     volts=(valPot*5/1023.0);

     lcd.setCursor(5,0);
     lcd.print("VOLTAJE");
     lcd.setCursor(0,1);
     lcd.print("POT Volts: ");
     lcd.print(volts);
     
          Key=teclado.getKey();        ///.waitForKey() != .getKey() porque el primero paraliza el codigo getkey NO
          if(Key>='A' && Key<='C')
          {
            OP=Key;
            lcd.clear();
            lcd.home();   
            lcd.print("DIGITE PASSWORD:");
            PW_input = password();
            if(PW_input==currentPW)
            flag1=true;
            else
            flag1=false;
        switch(flag1){
            case true:            
              if(OP=='A')//------------------------------------------>   ///GUARDAR DATOS
              {
                lcd.clear();
                lcd.home();
                lcd.print("Saving Data....");
                 for(i=2;i<2+4*sizeof(float);i+=sizeof(float))
                 {
                   valPot=analogRead(POT);
                   volts=(valPot*5/1023.0);
                   EEPROM.put(i, volts );
                   delay(1000);
                 }
                   lcd.clear();
                   lcd.home();
                   lcd.print("SAVED DATA");
                   delay(3000);
                   lcd.clear();
              }
              if(OP=='B')//-----------------------------------------------------> ///MOSTRAR DATOS
              {
                lcd.clear();
                lcd.home();
                j=0;//POSICION CERO(0) DEL VECTOR VEE[j]
                for(i=2;i<=2+4*sizeof(float);i+=sizeof(float))
                {
                  EEPROM.get(i,VEE[j]);//OBTENER DATOS i DE LA EEPROM y pasar al vector de 4 posiciones VEE[j]
                  j++;
                }
               lcd.setCursor(0,0);
               for(j=0;j<2;j++)
               {
                lcd.print(j+1);
                lcd.print(')');
                lcd.print(VEE[j]);
//                Serial.println(VEE[j]);
//                Serial.println(j);
                lcd.print("; ");
               }
               lcd.setCursor(0,1);
               for(j=2;j<4;j++)
               {
                lcd.print(j+1);
                lcd.print(')');
                lcd.print(VEE[j]);
//                Serial.println(VEE[j]);   
//                Serial.println(j);
                lcd.print("; ");               
               }
               delay(5000);
               lcd.clear();
              }
              if(OP=='C')//--------------------------------------------->///CAMBIAR PASSWORD
              {
               lcd.clear();
               lcd.home();   
               lcd.print("NEW PASSWORD:"); 
               PW_input = password();
               EEPROM.put(0,PW_input);
               currentPW=PW_input;
               lcd.clear();
               lcd.home();
               lcd.print("Saved Password:");          
               delay(2000);
               lcd.clear();
              }              
             break;        
            case false:            
             lcd.clear();
             lcd.home();
             lcd.print("INCORRECT PASSWORD");
             delay(2000); 
             lcd.clear();         
            break;
           }
          }   
//          else
//          {
//            lcd.clear();
//            lcd.home();
//            lcd.print("OPCION INVALIDA");
//            delay(2000);
//          }
}
