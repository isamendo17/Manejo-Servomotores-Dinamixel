#include <Dynamixel2Arduino.h>

// Configuración exclusiva para OpenRB-150
#define DXL_SERIAL   Serial1   // Puerto Dynamixel en OpenRB
#define DEBUG_SERIAL Serial    // Puerto USB para mensajes
#define DXL_DIR_PIN  -1        // OpenRB no requiere pin de dirección

const uint8_t DXL_ID = 2;                // ID del motor que vas a controlar
const float DXL_PROTOCOL_VERSION = 2.0;  // Protocolo usado por XL330

Dynamixel2Arduino dxl(DXL_SERIAL, DXL_DIR_PIN);

// Para usar nombres como LED, BAUD_RATE, etc.
using namespace ControlTableItem;

void setup() {
  DEBUG_SERIAL.begin(115200);
  while (!DEBUG_SERIAL);

  dxl.begin(57600);  // Debe coincidir con el baudrate del motor
  dxl.setPortProtocolVersion(DXL_PROTOCOL_VERSION);

  DEBUG_SERIAL.print("Buscando motor con ID ");
  DEBUG_SERIAL.print(DXL_ID);
  DEBUG_SERIAL.print("... ");

  if (dxl.ping(DXL_ID)) {
    DEBUG_SERIAL.println("Motor conectado.");
  } else {
    DEBUG_SERIAL.println("Motor no encontrado.");
    while (true); // Detener el programa
  }
}

void loop() {
  dxl.ledOn(DXL_ID);   // Encender LED del motor
  delay(500);
  dxl.ledOff(DXL_ID);  // Apagar LED
  delay(500);
}
