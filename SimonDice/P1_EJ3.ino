/**
* Practica 1 - Ejercicio 3
*
* Autores: Alba, Antonio y Gonzalo
**/
int led1= 12; // verde
int led2= 13; // rojo
int boton1 = 6; // botón de verde
int boton2 = 7; // botón de rojo
int pulsadoB1 = 0; // si se ha pulsado el boton1 == 1
int pulsadoB2 = 0; // si se ha pulsado el boton2 == 1
int pinBuzzer = 11; // Pin para el zumbador

int nivel= 0;

int dificultad = 3;
int secuencia[150];

int song[] = {261,349,392,440,392,330,-10,261,349,392,440,
  392,-10,-10,261,349,392,440,392,330,-10,330,349,330,261,
  261};

void setup() {
  Serial.begin(9600);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(boton1, INPUT);
  pinMode(boton2, INPUT);
  pinMode(pinBuzzer, OUTPUT);

  randomSeed(analogRead(0)); // Dejar el pin 0 desconectado para que de valores random
  digitalWrite(boton1, HIGH); //Cambiar dependiendo del pulsador
}

void loop() {
 if(nivel == 0){ // Primera ejecucion
    for (int i = 0; i < dificultad; i++){
      secuencia[i] = int(random(2, 4));
    }
    nivel = nivel + 1;
    mostrarSecuencia();
    jugar();
 }else{
   mostrarSecuencia();
   jugar();
 }
}

void mostrarSecuencia(){
  for (int i = 0; i < dificultad; i++){
    int led = 13;
    if(secuencia[i] == 2) led = led2;
    else if(secuencia[i] == 3) led = led1;
    Serial.println(secuencia[i]);
    digitalWrite(led, HIGH);
    tone(pinBuzzer,song[i]);
    delay(1000);
    digitalWrite(led, LOW);
    noTone(pinBuzzer);
    delay(500);
  }
}

void jugar(){
  int cont = 0;
  int ento[150];
  while(cont != dificultad){
    if(digitalRead(boton1) == HIGH){ //Cambiar dependiendo del pulsador
      digitalWrite(led1, HIGH);
      tone(pinBuzzer,song[cont]);
      delay(1000);
      ento[cont] = 3;
      cont++;
      digitalWrite(led1, LOW);
      noTone(pinBuzzer);
      Serial.println("Pulsado verde");
    }

    if(digitalRead(boton2) == HIGH){ //Cambiar dependiendo del pulsador
      digitalWrite(led2, HIGH);
      tone(pinBuzzer,song[cont]);
      delay(1000);
      ento[cont] = 2;
      cont++;
      digitalWrite(led2, LOW);
      noTone(pinBuzzer);
      Serial.println("Pulsado rojo");
    }
  }
  int numAciertos = 0;
  for (int i = 0; i < dificultad; i++){
    if(ento[i] == secuencia[i]) numAciertos++;
  }
  if(numAciertos == dificultad){
    subirNivel();
  }else{
    reiniciar();
  }
}


void subirNivel(){
  digitalWrite(2, LOW);
  digitalWrite(3, LOW);
  delay(500);
  nivel++;
  secuencia[dificultad] = int(random(2, 4));
  dificultad++;
  Serial.print("dificultad");
  Serial.println(dificultad);
}

void reiniciar(){
  digitalWrite(2, LOW);
  digitalWrite(3, LOW);
  delay(500);
  nivel = 1;
  dificultad = 3;
  for (int i = 0; i < dificultad; i++){
      secuencia[i] = int(random(2, 4));
  }
}
