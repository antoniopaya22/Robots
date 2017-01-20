/**
 * Programa para un robot con sensores de ultrasonidos
 *
 * @Autor : Antonio
 */


  // los pines digitales 2 y 3 controlan el motor derecho
  const int In1 = 1; // pin motor derecho
  const int In2 = 0; // pin motor derecho
  // los pines digitales 4 y 5 controlan el motor izquierdo
  const int In3 = 2; // pin motor izquierdo
  const int In4 = 3; // pin motor izquierdo
  //los pines digitales 9 y 10 habilitan los motores
  const int ENA = 8; // habilita el motor derecho
  const int ENB = 9; // habilita el motor izquierdo
  //los pines 4 y 5 son el echo y trigger del sensor izquierdo
  const int ech1 = 4; // echo sensor izquierdo
  const int trig1 = 5; // trigger sensor izquierdo
  //los pines 6 y 7 son el echo y trigger del sensor derecho
  const int ech2 = 6; // echo sensor derecho
  const int trig2 = 7; // trigger sensor derecho
  
  const int SPEED = 190; //velocidad de el motor 

/**
 * Metodo que inicializa los pines y variables
 */
void setup(){
  // put your setup code here, to run once:
  pinMode(In1, OUTPUT);
  pinMode(In2, OUTPUT);
  pinMode(In3, OUTPUT);
  pinMode(In4, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  analogWrite(ENA, SPEED);
  analogWrite(ENB, SPEED);
  pinMode(ech1,INPUT); //echo izq
  pinMode(trig1,OUTPUT); //trigger izq
  pinMode(ech2,INPUT); //echo der
  pinMode(trig2,OUTPUT); //trigger der
}

/**
 * Metodo que se repite en bucle
 */
void loop() {
  if(!chocaDer() && !chocaIzq()){
    alante(0,160);  
  }else if(chocaDer() && chocaIzq()){
    while(chocaDer() && chocaIzq()){
      atras(100,160);  
    }if(!chocaDer()){
      izquierda(200,SPEED);  
    }else if(!chocaIzq()){
      derecha(200,SPEED);
    }
  }else if(chocaDer()){
     izquierda(200,SPEED);  
  }else if(chocaIzq()){
     derecha(200,SPEED);
  }
}

/**
 * Metodo que hace que el robot avance
 */
void alante(int del,int speed) {
    analogWrite(ENA, speed);
    analogWrite(ENB, speed-40);
    digitalWrite(In1, HIGH);
    digitalWrite(In2, LOW); 
    digitalWrite(In3, HIGH);
    digitalWrite(In4, LOW);
    delay(del);
    analogWrite(ENA, SPEED);
    analogWrite(ENB, SPEED);
}

/**
 * Metodo que hace que el robot retroceda
 */
void atras(int del,int speed) {
    analogWrite(ENA, speed);
    analogWrite(ENB, speed);
    digitalWrite(In1, LOW);
    digitalWrite(In2, HIGH); 
    digitalWrite(In3, LOW);
    digitalWrite(In4, HIGH);
    delay(del);
    analogWrite(ENA, SPEED);
    analogWrite(ENB, SPEED);
}

/**
 * Metodo que hace que el robot gire a la derecha
 */
void derecha (int del,int speed) {
    analogWrite(ENB, speed);
    digitalWrite(In1, LOW);
    digitalWrite(In2, LOW); 
    digitalWrite(In3, HIGH);
    digitalWrite(In4, LOW);
    delay(del);
    analogWrite(ENB, SPEED);
}

/**
 * Metodo que hace que el robot gire a la izquierda
 */
void izquierda(int del,int speed) {
    analogWrite(ENA, speed);
    digitalWrite(In1, HIGH);
    digitalWrite(In2, LOW);
    digitalWrite(In3, LOW);
    digitalWrite(In4, LOW);
    delay(del);
    analogWrite(ENA, SPEED);
}

/*
 * Metodo que calcula si el sensor derecho localiza un obstaculo
 */
bool chocaIzq(){
    double distancia = 0;
    digitalWrite(trig1,LOW);
    delayMicroseconds(100); //Tiempo de espera 
    digitalWrite(trig1,HIGH);
    distancia = pulseIn(ech1,HIGH); //tiempo que dura el pulso
    distancia = distancia*0.034/2;
    if(distancia < 15) return true;
    else return false;
 }

/*
 * Metodo que calcula si el sensor derecho localiza un obstaculo
 */
bool chocaDer(){
    double distancia = 0;
    digitalWrite(trig2,LOW);
    delayMicroseconds(100); //Tiempo de espera 
    digitalWrite(trig2,HIGH);
    distancia = pulseIn(ech2,HIGH); //tiempo que dura el pulso
    distancia = distancia*0.034/2;
    if(distancia < 15) return true;
    else return false;
 }
