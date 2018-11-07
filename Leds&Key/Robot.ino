#include <TM1638.h>
// STB 10, CLK 9, DIO 8
TM1638 module(8, 9, 10);
long interval=400;
String bckp;
byte buttons;
unsigned long previousMillis = 0;
int song[] = {261,349,392,440,392,330,-10,261,349,392,440,
  392,-10,-10,261,349,392,440,392,330,-10,330,349,330,261,
  261};
int pinBuzzer = 11; // Pin para el zumbador
int echo = 4, trig = 5;
int pitidos;
double tiempo;
int veces = 1;
String frases[5] = {"HOLA CHICOS QUE TAL ESTAIS",
                    "YO BIEN GRACIAS",
                    "FALLASTE",
                    "QUE BIEN",
                    "ADIOS"};

void setup(){
  Serial.begin(9600);
  pinMode(pinBuzzer, OUTPUT);
  pinMode(echo,INPUT); //echo
  pinMode(trig,OUTPUT); //trigger
  tiempo = millis();
}
 
void loop(){
  if(getDistancia()< 15){
    apagarLeds();
    mostrarTexto(frases[0], 0);
    mostrarTexto(frases[1], 0);
  }else if(getDistancia() < 20){
    encenderLeds(1);
  }else if(getDistancia() < 30){
    encenderLeds(2);
  }else if(getDistancia() < 40){
    encenderLeds(3);
  }else if(getDistancia() < 50){
    encenderLeds(4);
  }else if(getDistancia() < 60){
    encenderLeds(5);
  }else if(getDistancia() < 70){
    encenderLeds(6);
  }else if(getDistancia() < 70){
    encenderLeds(7);
  }else
    encenderLeds(8);

  buttons=module.getButtons();
  //S1 = 1, S2 = 2, S3 = 4, S4 = 8
  //S5 = 16, S6 = 32, S7 = 64, S8 = 128
  if(buttons==1) {
    module.clearDisplay();
    module.setDisplayToString(frases[3]);
    tone(pinBuzzer,song[1]);
    delay(200);
    tone(pinBuzzer,song[4]);
    delay(200);
    tone(pinBuzzer,song[2]);
    delay(200);
    tone(pinBuzzer,song[8]);
    delay(200);
    tone(pinBuzzer,song[10]);
    delay(200);
    noTone(pinBuzzer);
    delay(1000);
  }else if (buttons==16) {
    module.clearDisplay();
    module.setDisplayToString(frases[4]);
    tone(pinBuzzer,song[10]);
    delay(200);
    tone(pinBuzzer,song[9]);
    delay(200);
    tone(pinBuzzer,song[3]);
    delay(200);
    tone(pinBuzzer,song[2]);
    delay(200);
    tone(pinBuzzer,song[1]);
    delay(200);
    noTone(pinBuzzer);
    delay(1000);
  }else if (buttons==128) {
    module.clearDisplay();
    module.setDisplayToString(frases[2]);
    tone(pinBuzzer,song[5]);
    delay(200);
    tone(pinBuzzer,song[6]);
    delay(200);
    tone(pinBuzzer,song[7]);
    delay(200);
    tone(pinBuzzer,song[8]);
    delay(200);
    tone(pinBuzzer,song[9]);
    delay(200);
    noTone(pinBuzzer);
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

void encenderLeds(int num){
  apagarLeds();
  for(int i=0; i<num; i++){
    module.setLED(TM1638_COLOR_RED, i);
  }
  delay(300);
}

void apagarLeds(){
  module.setLED(0, 0);
  module.setLED(0, 1);
  module.setLED(0, 2);
  module.setLED(0, 3);
  module.setLED(0, 4);
  module.setLED(0, 5);
  module.setLED(0, 6);
  module.setLED(0, 7);
}

void mostrarTexto(String texto, int sonidos){
  bool acabo = false;
  bckp = texto;
  pitidos = 5;
  while(!acabo){
    module.setDisplayToString(texto);
    unsigned long currentMillis = millis();
    if(millis()-tiempo > 400){
      pitidos--;
      tiempo = millis();
    }
    if(pitidos >= 0) tone(pinBuzzer,song[pitidos]);
    else noTone(pinBuzzer);
     
    if (currentMillis - previousMillis >= interval) {
      // save the last time you blinked the LED
      previousMillis = currentMillis;
      if(texto.length()>0){
        texto.remove(0, 1);
        if(texto.length()<8){
          module.clearDisplayDigit(texto.length(), false);
        }
      } else {
        texto = bckp;
        acabo == true;
        break;
      }
    }
  }
}
