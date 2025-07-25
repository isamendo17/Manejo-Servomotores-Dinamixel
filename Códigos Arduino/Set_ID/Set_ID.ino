#include <Dynamixel2Arduino.h>

#define DXL_SERIAL   Serial1   // Puerto Dynamixel en OpenRB-150
#define DEBUG_SERIAL Serial    // Para el monitor serie USB
#define DXL_DIR_PIN  -1        // OpenRB no necesita pin de dirección

const uint8_t CURRENT_ID = 3;   // ID actual del motor
const uint8_t NEW_ID     = 1;   // Nuevo ID al que quieres cambiar
const float DXL_PROTOCOL_VERSION = 2.0;

Dynamixel2Arduino dxl(DXL_SERIAL, DXL_DIR_PIN);
using namespace ControlTableItem;

void setup() {
  DEBUG_SERIAL.begin(115200);
  while (!DEBUG_SERIAL);

  dxl.begin(57600);  // Asegúrate de que el motor esté en 57600 bps
  dxl.setPortProtocolVersion(DXL_PROTOCOL_VERSION);

  DEBUG_SERIAL.print("Buscando motor con ID ");
  DEBUG_SERIAL.print(CURRENT_ID);
  DEBUG_SERIAL.print("... ");

  if (dxl.ping(CURRENT_ID)) {
    DEBUG_SERIAL.println("Motor encontrado.");
    dxl.torqueOff(CURRENT_ID);  // Desactiva el torque para poder cambiar ID

    if (dxl.setID(CURRENT_ID, NEW_ID)) {
      DEBUG_SERIAL.print("ID cambiado exitosamente a ");
      DEBUG_SERIAL.println(NEW_ID);
    } else {
      DEBUG_SERIAL.println("Error al cambiar el ID.");
    }
  } else {
    DEBUG_SERIAL.println("Motor no encontrado.");
  }
}

void loop() {
  // Nada en el loop
}