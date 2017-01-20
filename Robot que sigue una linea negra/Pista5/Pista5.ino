/*
 * Robot TEC declaracion de constantes
 */

 // Pines digitales 2 y 3, controlan el motor derecho.
const int In1 = 2; // Pin motor derecho
const int In2 = 3; // Pin motor derecho

 // Pines digitales 4 y 5, controlan el motor izquierdo.
const int In3 = 5; // Pin motor izquierdo
const int In4 = 4; // Pin motor izquierdo

 // Pines digitales 9 y 10, habilitan motores 
const int ENA = 9; // Habilita motor derecho
const int ENB = 10; // Habilita motor izquierdo

// Pines sensor optico.
const int PhotoSensorLeft = 6; // Pin del Arduino conectado al sensor optico izquierdo
const int PhotoSensorRight = 7; // Pin del Arduino conectado al sensor optico derecho

const int BLANCO = 0;
const int NEGRO = 1;

const int VELOCIDAD_AVANZAR = 170;

// Configuracion de las señales para el mov de los motores

void setup() {
 
 pinMode(In1, INPUT);
 pinMode(In2, INPUT);
 pinMode(In3, INPUT);
 pinMode(In4, INPUT);
 
 pinMode(ENA, INPUT);
 pinMode(ENB, INPUT);

 analogWrite(ENA, VELOCIDAD_AVANZAR);
 analogWrite(ENB, VELOCIDAD_AVANZAR);
   
}

void loop() {
 while(todoNegro()){
  avanzar();
 }
 
 while(todoBlanco()){
  retroceder();
  delay(100);
  girarIzquierda();
  delay(100);
  if(todoBlanco()){
    while(!todoNegro())
    girarDerecha();
  }
 }

 while(izquierdoBlanco()){
  girarDerecha();
 }

 
 while(derechoBlanco()){
  girarIzquierda();
 }
}

boolean todoNegro(){
  return (digitalRead(PhotoSensorLeft) == NEGRO && digitalRead(PhotoSensorRight) == NEGRO);
}

boolean todoBlanco(){
  return (digitalRead(PhotoSensorLeft) == BLANCO && digitalRead(PhotoSensorRight) == BLANCO);
}

boolean derechoBlanco(){
  return (digitalRead(PhotoSensorLeft) == NEGRO && digitalRead(PhotoSensorRight) == BLANCO);
}

boolean izquierdoBlanco(){
  return (digitalRead(PhotoSensorLeft) == BLANCO && digitalRead(PhotoSensorRight) == NEGRO);
}



void avanzar(){ 
  digitalWrite(In1, HIGH);
  digitalWrite(In2, LOW);
  digitalWrite(In3, HIGH);
  digitalWrite(In4, LOW);
}

void girarDerecha(){
  digitalWrite(In1, LOW);
  digitalWrite(In2, HIGH);
  digitalWrite(In3, HIGH);
  digitalWrite(In4, LOW);
}

void girarIzquierda(){
  digitalWrite(In1, HIGH);
  digitalWrite(In2, LOW);
  digitalWrite(In3, LOW);
  digitalWrite(In4, HIGH);
}

void retroceder(){
 analogWrite(ENA, VELOCIDAD_AVANZAR);
 analogWrite(ENB, VELOCIDAD_AVANZAR);
  
  digitalWrite(In1, LOW);
  digitalWrite(In2, HIGH);
  digitalWrite(In3, LOW);
  digitalWrite(In4, HIGH);
}
