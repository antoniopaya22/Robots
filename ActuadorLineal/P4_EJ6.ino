#include <Servo.h>

Servo servo1;
const int boton_pin = 2; // Pin para el boton pin2
const int x_pin = 0; // eje X A0
const int y_pin = 1; // eje Y A1
const int choque1 = 5;  // sensor choque 1
const int choque2 = 4;  // sensor choque 2
int modo = 0;
unsigned long tiempo;
unsigned long tiempo2;
int coordenadaActual;
int dir;
int precision = 48;

void setup() {
  Serial.begin(9600);
  servo1.attach(8);
  pinMode(boton_pin, INPUT);
  pinMode(choque1, INPUT);
  pinMode(choque2, INPUT);
  digitalWrite(boton_pin, HIGH);
}

void loop() {
  if(modo == 0){ // Calibrar
    calibrar();
    modo = 3;
  }
  if(modo == 1){ // Manual
    servo1.write(valorJoys());
    if(digitalRead(boton_pin) == LOW){
      if(modo == 1) modo = 2;
      else modo = 1;
    }
  }
  if(modo == 3){ // Leer coordenadas
    leer();
  }
  if(modo == 2){ // Automatico
    moverAuto();
  }
  delay(500);
}

int valorJoys(){
  if(analogRead(x_pin) > 913){
    return 0;
  }else if(analogRead(x_pin) > 812){
    return 85;
  }else if(analogRead(x_pin) > 412){
    return 90;
  }else if(analogRead(x_pin) > 50){
    return 95;
  }else{
    return 180;
  }
}

void calibrar(){
  dir = 0;
  servo1.write(dir);
  while(modo == 0){
    if(digitalRead(choque1) == LOW){
      dir = 180;
      servo1.write(dir);
      tiempo = millis();
    }
    if(digitalRead(choque2) == LOW){
      tiempo2 = millis();
      tiempo = (tiempo2 - tiempo)/precision;
      dir = 90;
      servo1.write(dir);
      coordenadaActual = 0;
      mover(12);
      modo = 3;
      break;
    }
  }
}

void leer(){
  String str = "";
  if(Serial.available() > 0){
    str = Serial.readStringUntil('\n');
    int anterior = 0;
    for(int i = 0; i < str.length(); i++){
      if(str[i] == ','){
        mover(str.substring(anterior,i).toInt());
        anterior = i+1;
      }else if(str[i] == ';'){
        delay(str.substring(anterior,i).toInt());
        anterior = i+1;
      }
    }
  }
}

void mover(int posicion){
  Serial.print("Moviendo hacia coordenada");
  Serial.println(posicion);
  if(posicion > 0 && posicion < precision){
    if(posicion > coordenadaActual){
      dir = 0;
    }else if(posicion == coordenadaActual){
      dir = 90;
    }else{
      dir = 180;
    }
    servo1.write(dir);
    delay(tiempo*(abs(posicion-coordenadaActual)));
    servo1.write(90);
    coordenadaActual = posicion;
  }else if(posicion <= 0){
    dir = 180;
    while(digitalRead(choque2) == HIGH){
      servo1.write(dir);
    }
    servo1.write(90);
    coordenadaActual = 0;
  }else if(posicion > precision){
    dir = 0;
    while(digitalRead(choque1) == HIGH){
      servo1.write(dir);
    }
    servo1.write(90);
    coordenadaActual = precision;
  }
}

void moverAuto(){
  int dir = 0;
  while(modo == 2){
    if(digitalRead(choque1) == LOW) dir = 180;
    if(digitalRead(choque2) == LOW) dir = 0;
    while(digitalRead(choque1) == HIGH && digitalRead(choque2) == HIGH){
      if(dir == 0) servo1.write(dir);
      else if(dir == 180) servo1.write(dir);
      if(digitalRead(boton_pin) == LOW){
        if(modo == 1) modo = 2;
        else modo = 1;
        return;
      }
    }
    
  }
}



