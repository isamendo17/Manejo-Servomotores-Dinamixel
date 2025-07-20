#include <Dynamixel2Arduino.h>

#define DXL_SERIAL   Serial1
#define DXL_DIR_PIN  -1
#define DEBUG_SERIAL Serial

const uint8_t DXL_ID_1 = 1;
const uint8_t DXL_ID_2 = 2;
const float DXL_PROTOCOL_VERSION = 2.0;

Dynamixel2Arduino dxl(DXL_SERIAL, DXL_DIR_PIN);
using namespace ControlTableItem;

void moveToInitialPosition(uint8_t id, float position_deg) {
  dxl.torqueOff(id);
  dxl.setOperatingMode(id, OP_POSITION);
  dxl.torqueOn(id);
  dxl.setGoalPosition(id, position_deg, UNIT_DEGREE);

  // Espera hasta que alcance la posición (con margen de error)
  while (abs(dxl.getPresentPosition(id, UNIT_DEGREE) - position_deg) > 1.0) {
    delay(10);
  }
}

void setup() {
  DEBUG_SERIAL.begin(115200);
  dxl.begin(57600);
  dxl.setPortProtocolVersion(DXL_PROTOCOL_VERSION);

  // Verificación de conexión
  if (!dxl.ping(DXL_ID_1) || !dxl.ping(DXL_ID_2)) {
    DEBUG_SERIAL.println("Uno o ambos motores no fueron detectados.");
    while (1);
  }

  // --- Posición inicial antes de oscilar ---
  moveToInitialPosition(DXL_ID_1, 230.0);
  moveToInitialPosition(DXL_ID_2, 130.0);

  // --- Configuración de modo VELOCIDAD ---
  dxl.torqueOff(DXL_ID_1);
  dxl.setOperatingMode(DXL_ID_1, OP_VELOCITY);
  dxl.torqueOn(DXL_ID_1);

  dxl.torqueOff(DXL_ID_2);
  dxl.setOperatingMode(DXL_ID_2, OP_VELOCITY);
  dxl.torqueOn(DXL_ID_2);
}

void loop() {
  // Fase 1: Giro positivo por 500 ms
  dxl.setGoalVelocity(DXL_ID_2, 15.0, UNIT_RPM);
  dxl.setGoalVelocity(DXL_ID_1, 10.0, UNIT_RPM);
  for (int i = 0; i < 50; i++) {
    float rpm2 = dxl.getPresentVelocity(DXL_ID_2, UNIT_RPM);
    float rpm1 = dxl.getPresentVelocity(DXL_ID_1, UNIT_RPM);
    DEBUG_SERIAL.print("RPM2:"); DEBUG_SERIAL.print(rpm2);
    DEBUG_SERIAL.print("\tRPM1:"); DEBUG_SERIAL.print(rpm1);
    DEBUG_SERIAL.print("\tMax:"); DEBUG_SERIAL.print(30);
    DEBUG_SERIAL.print("\tMin:"); DEBUG_SERIAL.println(-30);
    delay(10);
  }

  // Fase 2: Giro negativo por 500 ms
  dxl.setGoalVelocity(DXL_ID_2, -15.0, UNIT_RPM);
  dxl.setGoalVelocity(DXL_ID_1, -10.0, UNIT_RPM);
  for (int i = 0; i < 50; i++) {
    float rpm2 = dxl.getPresentVelocity(DXL_ID_2, UNIT_RPM);
    float rpm1 = dxl.getPresentVelocity(DXL_ID_1, UNIT_RPM);
    DEBUG_SERIAL.print("RPM2:"); DEBUG_SERIAL.print(rpm2);
    DEBUG_SERIAL.print("\tRPM1:"); DEBUG_SERIAL.print(rpm1);
    DEBUG_SERIAL.print("\tMax:"); DEBUG_SERIAL.print(30);
    DEBUG_SERIAL.print("\tMin:"); DEBUG_SERIAL.println(-30);
    delay(10);
  }
}
