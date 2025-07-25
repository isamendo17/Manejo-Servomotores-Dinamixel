#include <Dynamixel2Arduino.h>

#define DXL_SERIAL Serial1
const uint8_t DXL_ID = 1;
const float DXL_PROTOCOL_VERSION = 2.0;
const uint32_t DXL_BAUDRATE = 57600;
const uint32_t PROFILE_VELOCITY = 50;
const uint32_t PROFILE_ACCELERATION = 10;

Dynamixel2Arduino dxl(DXL_SERIAL);

void setup() {
  Serial.begin(9600);
  while (!Serial);

  dxl.begin();
  dxl.setPortProtocolVersion(DXL_PROTOCOL_VERSION);
  dxl.setBaudrate(DXL_ID, DXL_BAUDRATE);

  dxl.torqueOff(DXL_ID);
  dxl.setOperatingMode(DXL_ID, OP_POSITION);

  dxl.writeControlTableItem(PROFILE_VELOCITY, DXL_ID, 50);      // Velocidad Ajustable
  dxl.writeControlTableItem(PROFILE_ACCELERATION, DXL_ID, 10);  // Arranque Suave

  dxl.torqueOn(DXL_ID);

}

void loop() {
  if (Serial.available()) {
    String input = Serial.readStringUntil('\n');

    if (input.startsWith("POS_GRADOS:")) {
      float grados = input.substring(11).toFloat();
      grados = constrain(grados, 0.0, 180.0);
      uint16_t pos_dxl = static_cast<uint16_t>((270 - grados) / 180.0 * 4096);
      dxl.setGoalPosition(DXL_ID, pos_dxl);

      Serial.print("POS_GRADOS:");
      Serial.println(grados);
    }
  }
}
