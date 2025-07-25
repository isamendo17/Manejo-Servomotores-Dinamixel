#include <Dynamixel2Arduino.h>

#define DXL_SERIAL   Serial1
#define DXL_DIR_PIN  -1
#define DEBUG_SERIAL Serial

const uint8_t DXL_ID = 2;  // Cambia al ID de tu motor
const float DXL_PROTOCOL_VERSION = 2.0;

Dynamixel2Arduino dxl(DXL_SERIAL, DXL_DIR_PIN);
using namespace ControlTableItem;

void setup() {
  DEBUG_SERIAL.begin(115200);
  dxl.begin(57600);  // Asegúrate de que coincida con el baudrate de tu motor
  dxl.setPortProtocolVersion(DXL_PROTOCOL_VERSION);

  if (!dxl.ping(DXL_ID)) {
    DEBUG_SERIAL.println("Motor no detectado.");
    while (1);  // Detiene el programa si el motor no responde
  }

  dxl.torqueOff(DXL_ID);  // Desactiva torque para poder moverlo con la mano
  dxl.setOperatingMode(DXL_ID, OP_POSITION);
}

void loop() {
  float angle = dxl.getPresentPosition(DXL_ID, UNIT_DEGREE);
  DEBUG_SERIAL.println(angle);  // Puedes ver la posición en el Serial Plotter
  delay(100);  // Actualiza cada 100 ms
}
