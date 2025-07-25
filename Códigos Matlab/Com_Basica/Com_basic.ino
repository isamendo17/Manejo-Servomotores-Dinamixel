void setup() {
  Serial.begin(57600);  // Ajusta al mismo baud rate que MATLAB
}

void loop() {
  if (Serial.available()) {
    char cmd = Serial.read();
    if (cmd == 'H') {
      Serial.println("Hola desde OpenRB");
    }
  }
}
