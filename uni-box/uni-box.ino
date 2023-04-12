#include "access_point.h"
#include "uni_eeprom.h"
#include "client_mqtt.h"

int status = 0;
int doneInit = 0;

void setup() {
  Serial.begin(115200);
  setupEeprom();

  Serial.println();

  status = getStatus();
  Serial.println(status);

  int passwordLength = (int)EEPROM.read(ADDR_STATUS + 2);
  Serial.println(passwordLength);

  if (status == 1) {
    char* password;
    password = getPassword();
    Serial.println(password);

    char* ssid;
    ssid = getSSID();
    Serial.println(ssid);
    setupWifiClient(ssid, password);
  } else {
    setupAccessPoint();
  }
}

void loop() {
  if (status) {
    handleWifiClient();
  } else {
    handleClient();
  }
}
