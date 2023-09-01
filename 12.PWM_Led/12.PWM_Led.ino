#define ledpin 5
const int pot = A1;
float c=0;

void setup() {
  Serial.begin(9600);
  pinMode(ledpin, OUTPUT);
}

void loop() {
  c=analogRead(pot);
  analogWrite(ledpin, c/4);
  Serial.print(c/4);
  Serial.print(" ");
  delay(1000);
}
