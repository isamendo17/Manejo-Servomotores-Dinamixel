#include <Dynamixel2Arduino.h>

#define DXL_SERIAL Serial1
const uint8_t DXL_ID = 1;
const uint32_t DXL_BAUDRATE = 57600;

Dynamixel2Arduino dxl(DXL_SERIAL);

void setup() {
  Serial.begin(9600);
  while (!Serial);

  dxl.begin();
  dxl.setPortProtocolVersion(2.0);
  dxl.setBaudrate(DXL_ID, DXL_BAUDRATE);
  Serial.println("Listo para lectura de posición");

  dxl.torqueOff(DXL_ID);
}

void loop() {
  if (Serial.available()) {
    String input = Serial.readStringUntil('\n');

    if (input == "leer") {
      unsigned long t0 = millis();
      while (millis() - t0 < 5000) {
        float pos = dxl.getPresentPosition(DXL_ID);  // Lee posición en ticks
        float grados = map(pos, 0, 4095, 0, 180);     // Convierte a grados
        Serial.print("POS_GRADOS:");
        Serial.println(grados);
        delay(100);  // Envía cada 100 ms
      }
    }
  }
}

