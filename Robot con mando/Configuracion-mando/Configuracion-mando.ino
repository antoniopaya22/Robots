 
  // Incluimos la librería IR
  #include <IRLremote.h>
 
  // Pin digital 2 (INT0: Interrupción 0) --> Terminal de datos (S) del receptor IR
  const int interruptIR = 0;
 
  // Variables para recibir los datos
  uint8_t Protocolo = 0;  
  uint16_t Direccion = 0;
  uint32_t Comando = 0;
   
 
  void setup()
  {
    Serial.begin(115200);  // Comienzo de la comunicación serie
   
    Serial.println("Esperando lecturas IR...\n");
    IRLbegin<IR_ALL>(interruptIR); // Comienzo de la recepción IR
  }
 
  void loop()
  {
    // Si se ha leido un protocolo existente en la librería  
    if(Protocolo)
    {
      // Se presentan valores de protocolo, dirección y comando IR.
      Serial.println("-------------------------------");
      Serial.print("Protocolo:");
      Serial.println(Protocolo);
      Serial.print("Direccion:");
      Serial.println(Direccion, HEX);
      Serial.print("Comando:");
      Serial.println(Comando, HEX);
      Serial.println("-------------------------------");
     
      // Dependiendo del valor del comando, estaremos pulsando un botón u otro
      switch(Comando)
      {
        case 0xE01F:
          Serial.println("Boton -");
          break;
        case 0xA857:
          Serial.println("Boton +");            
          break;
        case 0x906F:
          Serial.println("Boton EQ");
          break;
        default:
          Serial.println("Boton sin etiquetar");
          break;
      }
      Serial.println("-------------------------------");
      Protocolo = 0;
    }
  }
 
  // Rutina de servicio de la interrupción INT 0 --> Pin 2 de Arduino
  void IREvent(uint8_t protocol, uint16_t address, uint32_t command)
  {
    // Se guardan los valores de protocolo, dirección y comando recibidos
    Protocolo = protocol;  
    Direccion = address;
    Comando = command;
  }
