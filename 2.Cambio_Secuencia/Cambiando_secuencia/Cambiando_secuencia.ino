byte L1= 2;
byte L2= 3;
byte L3= 4;
byte L4= 5;
byte L5= 6;
byte L6= 7;
byte L7= 8;
byte L8= 9;
byte L9= 10;
byte L10=11;
byte SW0= 12; //Toward right
byte SW1= 13; // toward left
long vel=55;
bool flag = true;

void setup() { 
  // put your setup code here, to run once:
for(int k=L1;k<=L7;k++)
{ pinMode(k, OUTPUT);
}
  pinMode(SW0, INPUT);
  pinMode(SW1, INPUT);
}

void loop() {
  switch(flag){
  case false:       //Towards Left
             for(int k=11;k>=-1;k--){ 
    if(k>-1){ digitalWrite(k, HIGH);
      } if(k<9){ digitalWrite(k+3, LOW);
             }delay(vel);
        if(digitalRead(SW0))//RIGHT BUTTON si presiono el boton con esto puedo salir en cualquier momento del ciclo
        { flag=true;k=-1;
        }if(digitalRead(SW1)){flag=false;k=-1;}//LEFT BUTTON si presiono el boton con esto puedo salir en cualquier momento del ciclo
      }
  break;
  
  case true:        //Towards Right
            int k=2;
            while(k<=16)
           { if(k<16)
              { digitalWrite(k, 1);
              }
            if(k>3){digitalWrite(k-3, 0);
            }delay(vel);
              if(digitalRead(SW0))//RIGHT BUTTON si presiono el boton con esto puedo salir en cualquier momento del ciclo
                { flag=true;
                  k=17;
                }
              if(digitalRead(SW1)==1)//LEFT BUTTON si presiono el boton con esto puedo salir en cualquier momento del ciclo
               {flag=false;
                k=17;
               }
             k++;
           } break;
        }             
}
