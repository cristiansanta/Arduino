int IN3 = 4; 
int IN4 = 3;
int EN1 = 6;

void setup()
{
  pinMode (IN4, OUTPUT);    // Input4 conectada al pin 4
  pinMode (IN3, OUTPUT);    // Input3 conectada al pin 5
  pinMode (EN1, OUTPUT);
}

void loop()
{
  // Motor gira en un sentido
  digitalWrite (IN4, HIGH);
  digitalWrite (IN3, LOW); 
   analogWrite(EN1,255);
  delay(1500);
  // Motor gira en sentido inverso
  digitalWrite (IN4, LOW);
  digitalWrite (IN3, HIGH);
  analogWrite(EN1,255);
  delay(1500);
}
