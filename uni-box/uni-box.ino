#include "access_point.h"
#include "uni_eeprom.h"

void setup() {
  Serial.begin(115200);
  setupAccessPoint();
  setupEeprom();
}

void loop() {
  handleClient();
}
