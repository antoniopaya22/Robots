#include <Keypad.h>
#include <TM1637.h>

const byte nfilas = 4;
const byte ncolumnas = 4;
char teclas[nfilas][ncolumnas] = {
    {'1','2','3','A'},
    {'4','5','6','B'},
    {'7','8','9','C'},
    {'*','0','#','D'}
  };
byte pfilas[nfilas] = {2, 3, 4, 5}; //Filas
byte pcolumnas[ncolumnas] = {A0, A1, A2, A3}; //Columnas
Keypad teclado = Keypad(makeKeymap(teclas), pfilas, pcolumnas, nfilas, ncolumnas);
String bufferLectura;
const int colVerde = 11, colRojo = 9, colAzul = 10;
double tiempo;
bool estadoPuerta = true;
String contra = "";
int contador = 0;
const int echo = 12, trig = 6;
int luzValue = 0;
int pinClk = 7;
int pinDio = 8;
TM1637 screen(pinClk,pinDio);
int contadorPersonas = 0;
int segundosPuerta = 5;
String numSegPuerta = "";
bool cambiandoSeg = false;

void setup() {
  // put your setup code here, to run once:
  bufferLectura = "";
  pinMode(colVerde,OUTPUT);
  pinMode(colRojo,OUTPUT);
  pinMode(colAzul,OUTPUT);
  digitalWrite(colVerde,HIGH);
  tiempo = 0;
  Serial.begin(9600);
  pinMode(echo,INPUT); //echo
  pinMode(trig,OUTPUT); //trigger
  screen.init();
  screen.set(BRIGHT_TYPICAL);
  delay(1500);
  screen.clearDisplay();
  screen.display(0,0);
  screen.display(1,0);
  screen.display(2,0);
  screen.display(3,0);
}

void abrirPuerta(bool saliendo){
  if(!saliendo){
    digitalWrite(colVerde,LOW);
    delay(1000);
    tiempo = millis();
    digitalWrite(colRojo,HIGH);
    estadoPuerta = false;
  }else{
    digitalWrite(colVerde,LOW);
    delay(1000);
    tiempo = millis();
    digitalWrite(colAzul,HIGH);
    estadoPuerta = false;
  }
  
}

void addPersona(){
  contadorPersonas += 1;
  int digito0 = contadorPersonas/1000;
  int digito1 = (contadorPersonas - digito0*1000)/100;
  int digito2 = (contadorPersonas - (digito0*1000 + digito1*100))/10;
  int digito3 = contadorPersonas - (digito0*1000 + digito1*100 + digito2*10);
  screen.clearDisplay();
  screen.display(0,digito0);
  screen.display(1,digito1);
  screen.display(2,digito2);
  screen.display(3,digito3);
  Serial.println(contadorPersonas);
}

void cerrarPuerta(char tecla){
  if(millis() - tiempo >= (segundosPuerta*1000) || tecla == 'C' || leerSensorLuz()){
    if(getDistancia() >= 10.0){
      estadoPuerta = true;
      tiempo = 0;
      digitalWrite(colAzul,LOW);
      digitalWrite(colRojo,LOW);
      digitalWrite(colVerde,HIGH);
      addPersona();
      delay(1000);
    }else{
      tiempo = millis();
    }
 }
}

void parpadear(int pin,int veces){
  for(int i=0; i < veces; i++){
    digitalWrite(pin,LOW);
    delay(200);
    digitalWrite(pin,HIGH);
    delay(200);
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

bool leerSensorLuz(){
  luzValue = analogRead(A5);
  //Serial.println(luzValue);
  if(luzValue < 80){
    return true;
  }else{
    return false;
  }
}

void loop() {
  char tecla = teclado.getKey();

  if(tecla == '*'){
    if(!cambiandoSeg){
      Serial.println("Cambiando seg");
      cambiandoSeg = true;
      numSegPuerta = "";
    }else{
      cambiandoSeg = false;
      segundosPuerta = numSegPuerta.toInt();
      numSegPuerta = "";
      contra = "";
      contador = 0;
      Serial.println("Hemos acabao manin de Cambiando seg");
    }
  }

  if(cambiandoSeg && tecla != '*' && tecla != '\0'){
    numSegPuerta += tecla;
    Serial.println(numSegPuerta);
  }
  
  else if (estadoPuerta && !cambiandoSeg && tecla!='*'){ //Si puerta cerrada
    if(tecla != '\0' && contador < 4){
      Serial.println("Holi"+contra);
      contra += tecla;
      contador++;
    }
    if(contra == "9876"){
      abrirPuerta(false);
      contador = 0;
      contra = "";
    }else if(contador == 4){
      parpadear(colVerde,3);
      contador = 0;
      contra = "";
    }
    if(leerSensorLuz()){
      abrirPuerta(true);
      while(leerSensorLuz()){
        delay(50);
      }
      if(getDistancia() >= 10.0){
        estadoPuerta = true;
        tiempo = 0;
        digitalWrite(colAzul,LOW);
        digitalWrite(colRojo,LOW);
        digitalWrite(colVerde,HIGH);
      }
    }
  }
  if (!estadoPuerta){
    cerrarPuerta(tecla);
  }
  
  
}



