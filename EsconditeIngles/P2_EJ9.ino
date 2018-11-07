#include <TM1637.h>


// Pantalla
int pinClk = 7;
int pinDio = 8;
TM1637 screen(pinClk,pinDio);
// Sensor ultrasonidos
const int echo = 12, trig = 6;
// Led RGB
const int colVerde = 11, colRojo = 9, colAzul = 10;

// Variables
boolean hasGanado = false;

void setup() {
  Serial.begin(9600);
  // Inicialización de variables
  hasGanado = false;
  
  // Inicialización led RGB
  pinMode(colVerde,OUTPUT);
  pinMode(colRojo,OUTPUT);
  pinMode(colAzul,OUTPUT);
  
  // Inicialización del sensor de ultrasonidos
  pinMode(echo,INPUT);
  pinMode(trig,OUTPUT);
  
  // Inicialización de la pantalla
  screen.init();
  screen.set(BRIGHT_TYPICAL);
  delay(1500);
  screen.clearDisplay();
  screen.display(0,0);
  screen.display(1,0);
  screen.display(2,0);
  screen.display(3,0);
  randomSeed(analogRead(0));
}

void loop() {
  // Cuenta atrás
  cuentaAtras();
  // Comprueba si se mueve algo
  comprobarSensor();
  // ¿Hay ganador?
  if (hasGanado){
    // Estallido de color
    ganar();
   }
}


void cuentaAtras(){
  // Cuenta aleatoria
  // La cuenta podrá ser, como máximo, desde 10
  int desde = random(5, 11);

  // Velocidad aleatoria
  // La velocidad será fijada por este valor
  int velocidad = random(3, 8);

  // Hacemos la cuenta atrás
  while(desde != 0){
    // Mostramos valor en la pantalla
    mostrarNumero(desde);
    // Hacemos delay
    delay(velocidad * 100);
    // Modificamos valor 'desde'
    desde--;
  }
}

int mostrarNumero(int n){
  int digito0 = n/1000;
  int digito1 = (n - digito0*1000)/100;
  int digito2 = (n - (digito0*1000 + digito1*100))/10;
  int digito3 = n - (digito0*1000 + digito1*100 + digito2*10);
  screen.clearDisplay();
  screen.display(0,digito0);
  screen.display(1,digito1);
  screen.display(2,digito2);
  screen.display(3,digito3);
  }


void comprobarSensor(){
  double distancia = getDistancia();
  if (distancia == 0) {comprobarSensor(); return;}
  if (distancia < 15){
    hasGanado = true;
    }
  else{
    double tiempo = millis();
    double antDistancia = 0;
    double nDistancia;
    // Comprobamos durante 5 segundos que nada modifique su posición
    while ( millis() - tiempo < 5000){
      antDistancia = nDistancia;
      nDistancia = getDistancia();
      Serial.println(abs(antDistancia - nDistancia));
      // Algo ha cambiado de posición? 
      // Igual así no funciona porque es muy sensible
      // Si no: 
      if (abs(antDistancia - nDistancia) > 200){
      //if (antDistancia != nDistancia){
        // Se ha perdido
        Serial.println("Holi");
        perder();
      }
      }
    }
  }

double getDistancia(){
  double distancia = 0;
  digitalWrite(trig,LOW);
  delayMicroseconds(100); //Tiempo de espera 
  digitalWrite(trig,HIGH);
  distancia = pulseIn(echo,HIGH); //tiempo que dura el pulso
  distancia = distancia*0.034/2;
  return distancia;
}

void perder(){
  digitalWrite(colRojo,HIGH);
  // Esperamos 15 segundos para que el jugador vuelva al lugar de salida
  delay(15000);
  digitalWrite(colRojo,LOW);
  hasGanado = false;
  // Inicialización de la pantalla
  screen.clearDisplay();
  screen.display(0,0);
  screen.display(1,0);
  screen.display(2,0);
  screen.display(3,0);
  }


void ganar(){
  double tiempo = millis();
  while (tiempo - millis() < 5000){
    int led = random(0, 3);
    if (led == 0){
      digitalWrite(colVerde,HIGH);
      digitalWrite(colAzul,LOW);
      digitalWrite(colRojo,LOW);
      }
    else if (led == 1){
      digitalWrite(colVerde,LOW);
      digitalWrite(colAzul,HIGH);
      digitalWrite(colRojo,LOW);
      }
    else{
      digitalWrite(colVerde,LOW);
      digitalWrite(colAzul,LOW);
      digitalWrite(colRojo,HIGH);
      }
    }
  hasGanado = false;
  // Inicialización de la pantalla
  screen.clearDisplay();
  screen.display(0,0);
  screen.display(1,0);
  screen.display(2,0);
  screen.display(3,0);
}
