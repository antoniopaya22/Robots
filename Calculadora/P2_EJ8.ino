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
byte pfilas[nfilas] = {2, 3, 4, 5}; //Filas
byte pcolumnas[ncolumnas] = {A0, A1, A2, A3}; //Columnas
Keypad teclado = Keypad(makeKeymap(teclas), pfilas, pcolumnas, nfilas, ncolumnas);
String bufferLectura;

// Pantalla
int pinClk = 7;
int pinDio = 8;
TM1637 screen(pinClk,pinDio);



int operando1, operando2;
char operacion;
String cadenaintroducida;



void setup() {
  Serial.begin(9600);
  bufferLectura = "";

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
  char tecla = teclado.getKey();
  if (tecla != '\0'){
    // Tenemos una tecla pulsada
    if (tecla == 'A' || tecla == 'B' || tecla == '*' || tecla == '#'){
      // Ya se ha introducido el primer operando y la operación
      if (cadenaintroducida.length() == 0){
        operando1 = 0;
        }
      else{
        operando1 = cadenaintroducida.toInt();
        } 
      operacion = tecla;
      cadenaintroducida = "";
      // En la pantalla mostrados 0000 - correspondiente al segundo operando
      screen.clearDisplay();
      screen.display(0,0);
      screen.display(1,0);
      screen.display(2,0);
      screen.display(3,0);
      }
    else if (tecla == 'C'){
      // Se calcula la solución
      if (cadenaintroducida.length() == 0){
        operando2 = 0;
        }
      else{
        operando2 = cadenaintroducida.toInt();
        } 
      // Almacenamos la solución en 'cadena introducida' para que pueda ser usada más tarde como 'operando 1'
      cadenaintroducida = calcularResultado();
      operacion = '\0';       
      operando2 = 0;

      // Mostramos en la pantalla
      if (cadenaintroducida.length() <= 4){
        // Mostramos el resultado
        mostrarNumero();
        }
      else{
        // Mostramos mensaje de error
        // Muestra 9999 
        screen.clearDisplay();
        screen.display(0,9);
        screen.display(1,9);
        screen.display(2,9);
        screen.display(3,9);
        }
      }
    else if (tecla == 'D'){
      // Se borra
      if (cadenaintroducida == ""){
        operando1 = 0;
        operacion = '\0';
        }
      else{
        cadenaintroducida = cadenaintroducida.substring(0, cadenaintroducida.length() - 1);
        }
      // Mostramos en la pantalla
        mostrarNumero();
      }
    else{
      // Se ha pulsado un número
      // Que hacemos si introduce 5 cifras? No se lee la 5? Ponemos el operando a 0? 
      cadenaintroducida += tecla;
      // Mostrar en la pantalla
      mostrarNumero();
      }
   }
}

String calcularResultado(){
  if (operacion == 'A'){
    return String(operando1 + operando2);
    }
  else if (operacion == 'B'){
    return String(operando1 - operando2);
    }
  else if (operacion == '*'){
    return String(operando1 * operando2);
    }
  else if (operacion == '#'){
    return String(operando1 / operando2);
    }
}

void mostrarNumero(){
  int resultado = cadenaintroducida.toInt();
  Serial.print(resultado);
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
