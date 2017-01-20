#include <math.h>    // (no semicolon)
/*
  Programa que mide la temperatura ambiente
 */


void setup() {
  Serial.begin(9600);
  // pin del sensor
  pinMode(0,INPUT);
}

void loop() {
  delay(10);
  double valor_digital = analogRead(0);
  double vo = valor_digital *(5.0/1023.0);
  double r =(5*10000.0/vo) -10000.0;
  double temp = 1/298.0 + (1/3900.0)*log(r/100000.0);
  double temperature = (1/temp) - 273;
  Serial.println(temperature);
  
}
