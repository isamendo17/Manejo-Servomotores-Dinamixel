#include <Dynamixel2Arduino.h>

#define DXL_SERIAL Serial1          // Puerto UART1 de la OpenRB-150
const uint8_t DXL_ID = 1;           // Cambia si tu motor tiene otro ID
const uint32_t DXL_BAUDRATE = 57600;
const uint32_t PROFILE_VELOCITY = 10;

Dynamixel2Arduino dxl(DXL_SERIAL);

void setup() {
  Serial.begin(9600);     // Comunicación con MATLAB
  while (!Serial);        // Espera a que el puerto esté listo

  dxl.begin();
  dxl.setPortProtocolVersion(2.0);
  dxl.setBaudrate(DXL_ID, DXL_BAUDRATE);

  // Cambia a modo posición
  dxl.torqueOff(DXL_ID);
  dxl.setOperatingMode(DXL_ID, OP_POSITION);
  dxl.writeControlTableItem(PROFILE_VELOCITY, DXL_ID, PROFILE_VELOCITY);
  dxl.torqueOn(DXL_ID);

  Serial.println("Listo para recibir posiciones");
}

void loop() {
  if (Serial.available()) {
    String input = Serial.readStringUntil('\n');  // Leer línea completa
    int pos = input.toInt();                      // Convertir a número

    if (pos >= 0 && pos <= 1023) {                // Rango válido para muchos Dynamixel AX/MX
      dxl.setGoalPosition(DXL_ID, pos);
      Serial.print("Moviendo a: ");
      Serial.println(pos);
    } else {
      Serial.print("Valor fuera de rango: ");
      Serial.println(pos);
    }
  }
}