#include <Dynamixel2Arduino.h>

// Configuración para OpenRB-150
#define DXL_SERIAL   Serial1
#define DEBUG_SERIAL Serial
#define DXL_DIR_PIN  -1

const uint8_t DXL_ID_1 = 1;
const uint8_t DXL_ID_2 = 2;
const float DXL_PROTOCOL_VERSION = 2.0;

Dynamixel2Arduino dxl(DXL_SERIAL, DXL_DIR_PIN);
using namespace ControlTableItem;

void setup() {
  DEBUG_SERIAL.begin(115200);
  while (!DEBUG_SERIAL);

  dxl.begin(57600);  // Debe coincidir con el baudrate configurado en ambos motores
  dxl.setPortProtocolVersion(DXL_PROTOCOL_VERSION);

  // Verificar ambos motores
  if (!dxl.ping(DXL_ID_1)) {
    DEBUG_SERIAL.println("Motor ID 1 no encontrado.");
    while (1);
  }
  if (!dxl.ping(DXL_ID_2)) {
    DEBUG_SERIAL.println("Motor ID 2 no encontrado.");
    while (1);
  }

  DEBUG_SERIAL.println("Ambos motores detectados. Configurando...");

  // Apagar torque para cambiar modo
  dxl.torqueOff(DXL_ID_1);
  dxl.torqueOff(DXL_ID_2);

  // Modo posición extendida para permitir ángulos amplios
  dxl.setOperatingMode(DXL_ID_1, OP_EXTENDED_POSITION);
  dxl.setOperatingMode(DXL_ID_2, OP_EXTENDED_POSITION);

  // Activar torque
  dxl.torqueOn(DXL_ID_1);
  dxl.torqueOn(DXL_ID_2);

  // Velocidad moderada
  dxl.writeControlTableItem(PROFILE_VELOCITY, DXL_ID_1, 50);
  dxl.writeControlTableItem(PROFILE_VELOCITY, DXL_ID_2, 50);
}

void loop() {
  // Estado A: ID 1 → 340°, ID 2 → 115°
  float objetivo1 = 340.0;
  float objetivo2 = 115.0;

  dxl.setGoalPosition(DXL_ID_1, objetivo1, UNIT_DEGREE);
  dxl.setGoalPosition(DXL_ID_2, objetivo2, UNIT_DEGREE);

  float pos1, pos2;
  do {
    pos1 = dxl.getPresentPosition(DXL_ID_1, UNIT_DEGREE);
    pos2 = dxl.getPresentPosition(DXL_ID_2, UNIT_DEGREE);
    DEBUG_SERIAL.print("M1: ");
    DEBUG_SERIAL.print(pos1);
    DEBUG_SERIAL.print("°, M2: ");
    DEBUG_SERIAL.println(pos2);
    delay(100);
  } while (abs(pos1 - objetivo1) > 1.0 || abs(pos2 - objetivo2) > 1.0);

  delay(1000);

  // Estado B: ID 1 → 220°, ID 2 → 250°
  objetivo1 = 220.0;
  objetivo2 = 250.0;

  dxl.setGoalPosition(DXL_ID_1, objetivo1, UNIT_DEGREE);
  dxl.setGoalPosition(DXL_ID_2, objetivo2, UNIT_DEGREE);

  do {
    pos1 = dxl.getPresentPosition(DXL_ID_1, UNIT_DEGREE);
    pos2 = dxl.getPresentPosition(DXL_ID_2, UNIT_DEGREE);
    DEBUG_SERIAL.print("M1:");
    DEBUG_SERIAL.print(pos1);
    DEBUG_SERIAL.print("\tM2:");
    DEBUG_SERIAL.println(pos2);
    delay(100);
  } while (abs(pos1 - objetivo1) > 1.0 || abs(pos2 - objetivo2) > 1.0);

  delay(1000);
}
