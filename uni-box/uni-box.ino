#include "access_point.h"
#include "uni_eeprm.h";

void setup() {
  Serial.begin(115200);
  setupAccessPoint();
  setupEeprom();
}

void loop() {
  handleClient();
}
