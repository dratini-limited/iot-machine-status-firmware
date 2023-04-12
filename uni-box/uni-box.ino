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

  char* password;
  password = getPassword();
  Serial.println(password);

  char* ssid;
  ssid = getSSID();
  Serial.println(ssid);

  if (status == 1) {
    setupWifiClient(ssid, password);
  }

  // if (status == 1) {
  //   char* ssid;
  //   ssid = getSSID();
  //   Serial.println(ssid);

  //   char* password;
  //   password = getPassword();
  //   Serial.println(password);

  //   setupWifiClient(ssid, password);
  // }
  // else {
  //   setupAccessPoint();
  // }
}

void loop() {
  // if (doneInit) {
  //   if (status) {
  //     handleWifiClient();
  //   } else {
  //     handleClient();
  //   }
  // }
}
