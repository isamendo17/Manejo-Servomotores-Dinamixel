#include <Dynamixel2Arduino.h>

// Configuración para OpenRB-150
#define DXL_SERIAL   Serial1
#define DEBUG_SERIAL Serial
#define DXL_DIR_PIN  -1

#define MAX_BAUD 5
const int32_t baudrates[MAX_BAUD] = {57600, 115200, 1000000, 2000000, 3000000};

Dynamixel2Arduino dxl(DXL_SERIAL, DXL_DIR_PIN);
using namespace ControlTableItem;

void setup() {
  int found_dynamixel = 0;

  DEBUG_SERIAL.begin(115200);
  while (!DEBUG_SERIAL);

  for (int protocol = 1; protocol <= 2; protocol++) {
    dxl.setPortProtocolVersion((float)protocol);
    DEBUG_SERIAL.print("Protocolo ");
    DEBUG_SERIAL.println(protocol);

    for (int i = 0; i < MAX_BAUD; i++) {
      dxl.begin(baudrates[i]);
      DEBUG_SERIAL.print("Baudrate: ");
      DEBUG_SERIAL.println(baudrates[i]);

      for (int id = 0; id < DXL_BROADCAST_ID; id++) {
        if (dxl.ping(id)) {
          DEBUG_SERIAL.print("ID: ");
          DEBUG_SERIAL.print(id);
          DEBUG_SERIAL.print(" | Modelo: ");
          DEBUG_SERIAL.println(dxl.getModelNumber(id));
          found_dynamixel++;
        }
      }
    }
  }

  DEBUG_SERIAL.print("Total motores encontrados: ");
  DEBUG_SERIAL.println(found_dynamixel);
}

void loop() {
  // No se requiere ejecución continua
}
