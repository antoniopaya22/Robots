
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
  const int SPEED = 200;

  int last = 0;
  boolean goneBack;
  int matriz[2];
  boolean turning = false;
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
      izquierda(100);
  }
   //Hacia la derecha
  else if (valLeft == BLANCO && valRight == NEGRO) {
     derecha(100);
  } 
  //Hacia atras
  else{
    turning = true;
   /** if (goneBack) {
     atras(100);
     //Si la ultima vez que giro era a la izquierda
     if (last == -1 || last == 0) {
      izquierda(180);      
    }else if (last == 1){
      derecha(180);
    }
    
    } else {
     atras(200);
    }
    goneBack = !goneBack;
  }*/
  if (matriz[0] == 1 && matriz[1] == 1) {
   matriz[0] = 0;
   matriz[1] = 0;

   atras(150);  
   izquierda(300);
  } else {
  atras(150);
  izquierda(100);
  }
  }
}

  void alante(int del) {
     digitalWrite(In1, HIGH);
      digitalWrite(In2, LOW); 
      digitalWrite(In3, HIGH);
      digitalWrite(In4, LOW);
      last = 0;
      goneBack = false;
      matriz[0] = 0;
      matriz[1] = 0;
      
  }
  void atras(int del) {
    digitalWrite(In1, LOW);
     digitalWrite(In2, HIGH); 
     digitalWrite(In3, LOW);
     digitalWrite(In4, HIGH);
     delay(del);
  }

  void derecha (int del) {
    if (!turning) {
    digitalWrite(In1, LOW);
     digitalWrite(In2, LOW); 
     digitalWrite(In3, HIGH);
     digitalWrite(In4, LOW);
     
     last = 1;
     matriz[1] = 1;
    }
    turning = false;
    delay(del);
  }

  void izquierda(int del) {
     digitalWrite(In1, HIGH);
      digitalWrite(In2, LOW);
      digitalWrite(In3, LOW);
      digitalWrite(In4, LOW);
      delay(del);
      last = -1;
      matriz[0] = 1;
  }
