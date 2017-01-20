/**
 * @author Antonio Paya
 */

void setup() {
  pinMode(3,INPUT); //echo
  pinMode(4,OUTPUT); //trigger
  Serial.begin(9600);
}

void loop() {
  double llegada = 0;
  digitalWrite(4,LOW);
  delayMicroseconds(100); //Tiempo de espera 
  digitalWrite(4,HIGH);
  llegada = pulseIn(3,HIGH); //tiempo que dura el pulso
  llegada = llegada*0.034/2;
  Serial.println(llegada);
}
