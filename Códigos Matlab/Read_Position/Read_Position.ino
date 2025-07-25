#include <Dynamixel2Arduino.h>

#define DXL_SERIAL Serial1
const uint8_t DXL_ID = 1;
const uint32_t DXL_BAUDRATE = 57600

Dynamixel2Arduino dxl(DXL_SERIAL);

void setup() {
  Serial.begin(9600);
  while (!Serial);

  dxl.begin();
  dxl.setPortProtocolVersion(2.0);
  dxl.setBaudrate(DXL_ID, DXL_BAUDRATE);
  Serial.println("Listo para lectura de posición");

  dxl.torqueOn(DXL_ID);
}

void loop() {
  if (Serial.available()) {
    char cmd = Serial.read();

    if (cmd == 'P') {
      uint16_t pos = dxl.getPresentPosition(DXL_ID);
      float angle_deg = (pos / 1023.0) * 180.0;

      Serial.print("POS_GRADOS:");
      Serial.println(angle_deg, 2);  // Enviar con 2 decimales
    }
