
  // los pines digitales 2 y 3 controlan el motor derecho
  const int In1 = 2; // pin motor derecho
  const int In2 = 3; // pin motor derecho
  // los pines digitales 4 y 5 controlan el motor izquierdo
  const int In3 = 4; // pin motor izquierdo
  const int In4 = 5; // pin motor izquierdo
  //los pines digitales 9 y 10 habilitan los motores
  const int ENA = 9; // habilita el motor derecho
  const int ENB = 10; // habilita el motor izquierdo

  const int PhotoSensorLeft = 6; // pin del Arduino conectado al sensor óptico Izquierdo
  const int PhotoSensorRight = 7; // pin del Arduino conectado al sensor óptico Derecho
  // constantes
  const int BLANCO = 0;
  const int NEGRO = 1;

  const int DELAY = 1;
  const int SPEED = 180;
  bool last;

  bool vector[] = {false, false};

void setup(){
  // put your setup code here, to run once:
  pinMode(In1, OUTPUT);
  pinMode(In2, OUTPUT);
  pinMode(In3, OUTPUT);
  pinMode(In4, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(PhotoSensorLeft,INPUT);
  pinMode(PhotoSensorRight,INPUT);
  analogWrite(ENA, SPEED);
  analogWrite(ENB, SPEED);
}

void loop() {
  int valLeft = digitalRead(PhotoSensorLeft);
  int valRight = digitalRead(PhotoSensorRight);

   //Hacia delante
  if (valLeft == NEGRO && valRight == NEGRO) {
     alante(0);
  } 
   //Hacia la izquierda
  else if (valLeft == NEGRO && valRight == BLANCO) {
      izquierda(50);
      last=true;
  }
   //Hacia la derecha
  else if (valLeft == BLANCO && valRight == NEGRO) {
     derecha(50);
     last = false;
  } 
  //Hacia atras
  else{
    atras(150);
  }
  
}

  void alante(int del) {
     digitalWrite(In1, HIGH);
      digitalWrite(In2, LOW); 
      digitalWrite(In3, HIGH);
      digitalWrite(In4, LOW);
      delay(del);
  }
  void atras(int del) { 
     digitalWrite(In1, LOW);
     digitalWrite(In2, HIGH); 
     digitalWrite(In3, LOW);
     digitalWrite(In4, HIGH);
     delay(del + 50);

      if (vector[0] && vector[1]) {
        vector[0] = false;
        vector[1] = false;
        delay(del);
    }
     if(last) {
      vector[1] = true;
      izquierda(del);
     }
     else {
      vector[0] = true;
      derecha(del);
     
    }

   
  }

  void derecha (int del) {
    digitalWrite(In1, LOW);
     digitalWrite(In2, LOW); 
     digitalWrite(In3, HIGH);
     digitalWrite(In4, LOW);
    delay(del);
  }

  void izquierda(int del) {
     digitalWrite(In1, HIGH);
      digitalWrite(In2, LOW);
      digitalWrite(In3, LOW);
      digitalWrite(In4, LOW);
      delay(del);
  }
