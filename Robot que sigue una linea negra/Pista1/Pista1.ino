/**
 * Programa para un robot con una placa Arduino Uno que debe de seguir un circuito de color negro sin salirse 
 *
 * @Autor : Antonio
 */


  // los pines digitales 2 y 3 controlan el motor derecho
  const int In1 = 3; // pin motor derecho
  const int In2 = 2; // pin motor derecho
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
  
  const int SPEED = 190; //velocidad de el motor 
  bool matriz[2];         //matriz de booleanos que guardan el ultimo giro realizado, siendo la posicion 0 la izquierda y la 1 la derecha

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
  pinMode(PhotoSensorLeft,INPUT);
  pinMode(PhotoSensorRight,INPUT);
  analogWrite(ENA, SPEED);
  analogWrite(ENB, SPEED);
}

/**
 * Metodo que se repite en bucle
 */
void loop() {
	
  	int valLeft = digitalRead(PhotoSensorLeft);
  	int valRight = digitalRead(PhotoSensorRight);

  	//Hacia delante
  	if (valLeft == NEGRO && valRight == NEGRO) {
  	    alante(0,145);
  	} 
    //Hacia la izquierda
    else if (valLeft == NEGRO && valRight == BLANCO) {
        izquierda(100,SPEED);
    }
    //Hacia la derecha
    else if (valLeft == BLANCO && valRight == NEGRO) {
		    derecha(100,SPEED);
    } 
    //Hacia atras
    else{
    		if (matriz[0] == 1 && matriz[1] == 1) {
      			matriz[0] = 0;
      			matriz[1] = 0;
      			atras(150,SPEED);  
      			izquierda(350,SPEED);
    		}else {
      			atras(150,SPEED);
      			izquierda(150,180);
    		}
	}
}

/**
 * Metodo que hace que el robot avance
 */
void alante(int del,int speed) {
    analogWrite(ENA, speed);
    analogWrite(ENB, speed);
    digitalWrite(In1, LOW);
    digitalWrite(In2, HIGH); 
    digitalWrite(In3, LOW);
    digitalWrite(In4, HIGH);
    matriz[0] = 0;
    matriz[1] = 0;
    analogWrite(ENA, SPEED);
    analogWrite(ENB, SPEED);
}

/**
 * Metodo que hace que el robot retroceda
 */
void atras(int del,int speed) {
    analogWrite(ENA, speed);
    analogWrite(ENB, speed);
    digitalWrite(In1, HIGH);
    digitalWrite(In2, LOW); 
    digitalWrite(In3, HIGH);
    digitalWrite(In4, LOW);
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
    digitalWrite(In3, LOW);
    digitalWrite(In4, HIGH);
    delay(del);
    matriz[1] = 1;
    analogWrite(ENB, SPEED);
}

/**
 * Metodo que hace que el robot gire a la izquierda
 */
void izquierda(int del,int speed) {
    analogWrite(ENA, speed);
    digitalWrite(In1, LOW);
    digitalWrite(In2, HIGH);
    digitalWrite(In3, LOW);
    digitalWrite(In4, LOW);
    delay(del);
    matriz[0] = 1;
    analogWrite(ENA, SPEED);
  }
