/*
  Programa que utiliza un potenciometro
 */

double valorPotenciometro = 0;

void setup() {
  Serial.begin(9600);
  // el potenciometro es el pin analogico 0
  pinMode(A0, INPUT);
  pinMode(3,OUTPUT);
}

void loop() {
  double cero5 = (analogRead(A0)*5.0)/1023.0;
  valorPotenciometro = analogRead(A0);
  Serial.println(cero5);
  valorPotenciometro = valorPotenciometro*(255.0/1023.0);
  Serial.println( valorPotenciometro);
  analogWrite(3,valorPotenciometro);
  delay(1000);
}
