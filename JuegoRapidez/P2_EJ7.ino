#include <Keypad.h>
#include <TM1637.h>

// Teclado
const byte nfilas = 4;
const byte ncolumnas = 4;
char teclas[nfilas][ncolumnas] = {
    {'1','2','3','A'},
    {'4','5','6','B'},
    {'7','8','9','C'},
    {'*','0','#','D'}
  };

// Teclado 1
byte pfilas[nfilas] = {2, 3, 4, 5}; //Filas1
byte pcolumnas[ncolumnas] = {A0, A1, A2, 0}; //Columnas1
Keypad teclado = Keypad(makeKeymap(teclas), pfilas, pcolumnas, nfilas, ncolumnas);

// Teclado 2
byte pfilas2[nfilas] = {9, 10, 11, 12}; //Filas2
byte pcolumnas2[ncolumnas] = {A3, A4, A5, 6}; //Columnas2
Keypad teclado2 = Keypad(makeKeymap(teclas), pfilas2, pcolumnas2, nfilas, ncolumnas);

// Pantalla
int pinClk = 7;
int pinDio = 8;
TM1637 screen(pinClk,pinDio);


char operadores[4] = {'+','-','*','/'};
String respuesta1 = "";
String respuesta2 = "";
String modo;
int rondas = 10;
double tiempos[2];
int contador = 0;

/**
 * Como jugar:
 *  -> Se inicia la partida y se eligen por teclado el numero de rondas
 *  -> Se muestra una operacion y se debe escribir el resultado (2 digitos)
 *  -> # para mostrar que se ha acabado
 *  -> * para parar la partida
 **/
void setup() {
  Serial.begin(9600);

  screen.init();
  screen.set(BRIGHT_TYPICAL);
  delay(1500);
  screen.clearDisplay();
  screen.display(0,0);
  screen.display(1,0);
  screen.display(2,0);
  screen.display(3,0);
}

void loop() {
  startGame();
  while(rondas > 0){
    jugar();
    rondas--;
  }
}

void jugar(){
  double * p;
  modo = "partida";
  int result = mostrarOperacion();
  respuesta1 = "";
  respuesta2 = "";
  esperarRespuesta();
  Serial.print("====Ronda"); Serial.print(rondas); Serial.println("====");
  Serial.print("Respuesta jugador 1: ");
  Serial.print(respuesta1);
  Serial.print("  Tiempo: ");
  Serial.println(tiempos[0]);
  Serial.print("Respuesta jugador 2: ");
  Serial.print(respuesta2);
  Serial.print("  Tiempo: ");
  Serial.println(tiempos[1]);
  Serial.print("------> Solucion ");
  Serial.println(result);
  Serial.print("Ganador: ");
  if (tiempos[0] < tiempos[1] && respuesta2.toInt() == result && respuesta1.toInt() != result) {
     Serial.println("Jugador 2");
     contador += 100;
  }
  else if(tiempos[1] < tiempos[0] && respuesta1.toInt() == result && respuesta2.toInt() != result){
     Serial.println("Jugador 1");
     contador += 1;
  }
  else if (respuesta2.toInt() == result) {
     Serial.println("Jugador 2");
     contador += 100;
  }
  else if(respuesta1.toInt() == result){
     Serial.println("Jugador 1");
     contador += 1;
  }
  else Serial.println("No hay ganador. Es un empate");
  mostrarNumero(contador);
}

void esperarRespuesta(){
  double inicio = millis();
  double tiempoPausa;
  char tecla = teclado.getKey();
  char tecla2 = teclado2.getKey();
  bool finalizo1 = false;
  bool finalizo2 = false;

  while (!finalizo1 || !finalizo2){
    tecla = teclado.getKey();
    tecla2 = teclado2.getKey();
    if(tecla == '*' || tecla2 == '*'){
      if(modo == "partida"){
        Serial.print("------> Partida en pausa");
        modo = "stop";
        tiempoPausa = millis();
      }else{
        Serial.print("------> Partida reanudada");
        modo = "partida";
        tiempoPausa = millis() - tiempoPausa;
        inicio = inicio + tiempoPausa;
      }
    }
    if (tecla != '\0' && tecla != '*' && modo == "partida"){
      if(tecla == '#'){
        tiempos[0] = millis() - inicio;
        finalizo1 = true;
        Serial.println("Acabo1");
      }else if(respuesta1.length() < 2){
        respuesta1 += tecla;
        Serial.println(respuesta1);
      }
    }
    if (tecla2 != '\0' && tecla2 != '*' && modo == "partida"){
      if(tecla2 == '#'){
        tiempos[1] = millis() - inicio;
        finalizo2 = true;
        Serial.println("Acabo2");
      }else if(respuesta2.length() < 2){
        respuesta2 += tecla2;
        Serial.println(respuesta2);
      }
    }
  }
}

int mostrarOperacion(){
  int op1 = random(1,10);
  int op2 = random(1,10);
  char op = operadores[random(0, 4)];
  int resultado;
  if(op2 > op1) resultado = calcular(op2,op1,op);
  else resultado = calcular(op1,op2,op);
  return resultado;
}

double calcular(int op1, int op2, char op){
  int resultado = 0;
  switch (op) {
    case '+':
      Serial.print("Operacion: ");
      Serial.print(op1);
      Serial.print(op);
      Serial.print(op2);
      resultado = op1 + op2;
      break;
    case '-':
      Serial.print("Operacion: ");
      Serial.print(op1);
      Serial.print(op);
      Serial.print(op2);
      resultado = op1 - op2;
      break;
    case '*':
      Serial.print("Operacion: ");
      Serial.print(op1);
      Serial.print(op);
      Serial.print(op2);
      resultado = op1 * op2;
      break;
    case '/':
      Serial.print("Operacion: ");
      Serial.print(op1);
      Serial.print(op);
      Serial.print(op2);
      resultado = op1 / op2;
      break;
  }
  Serial.println();
  return resultado;
}

void mostrarNumero(int resultado){
  int digito0 = resultado/1000;
  int digito1 = (resultado - digito0*1000)/100;
  int digito2 = (resultado - (digito0*1000 + digito1*100))/10;
  int digito3 = resultado - (digito0*1000 + digito1*100 + digito2*10);
  screen.clearDisplay();
  screen.display(0,digito0);
  screen.display(1,digito1);
  screen.display(2,digito2);
  screen.display(3,digito3);
}



void startGame(){
  Serial.println("======================================");
  Serial.println("      Juego de rapidez");
  Serial.println("======================================");
  Serial.println("Escribe el numero de rondas (<10): ");

  Serial.print("La partida comienza en: 3...");
  delay(1000);
  Serial.print("2...");
  delay(1000);
  Serial.print("1...");
  delay(1000);
  Serial.println("YA!!!");
}
