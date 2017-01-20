/*
 Programa que utiliza dos servomotores
*/

#include <Servo.h>

Servo myservo;  // Crea el objeto servo
Servo myservo2;  // Crea el objeto servo
int val1;
int val2;

void setup() {
  myservo.attach(3); 
 myservo2.attach(2); 
}

void loop() {
  val1 = analogRead(A0);            // lee el valor del potenciometro (entre 0 y 1023)
  val1 = map(val1, 0, 1023, 0, 180);     // (valor entre 0 y 180)
  val2 = analogRead(A1);            
  val2 = map(val2, 0, 1023, 0, 180);    
  
  myservo.write(val1);                  
  myservo2.write(val2);                  
  delay(15);                           
}
