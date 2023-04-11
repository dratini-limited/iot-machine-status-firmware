#include "uni_eeprom.h"


int addrSsid = 0;       // 0->30
int addrPassword = 31;  // 31-51
int addrStatus = 52;

void setupEeprom() {
  EEPROM.begin(512);
}

void setWifi(char* ssid, char* password) {
  int ssidLength = strlen(ssid);
  int passwordLength = strlen(password);

  EEPROM.write(addrStatus, 1);
  EEPROM.write(addrStatus + 1, ssidLength);
  EEPROM.write(addrStatus + 2, ssidLength);

  for (int i = 0; i < ssidLength; i++) {
    EEPROM.write(addrSsid + i, ssid[i]);
  }

  for (int i = 0; i < passwordLength; i++) {
    EEPROM.write(addrPassword + i, password[i]);
  }
}

char* getSSID() {
  char ssidLength = EEPROM.read(addrStatus + 1);
  char str [ssidLength];
  for (int i = 0; i < ssidLength; i++) {
    str[i] = EEPROM.read(addrSsid + i);
  }

  return str;
}

char* getPassword() {
  char passwordLength = EEPROM.read(addrStatus + 2);
  char str [passwordLength];
  for (int i = 0; i < passwordLength; i++) {
    str[i] = EEPROM.read(addrPassword + i);
  }

  return str;
}

char getStatus() {
  char a = EEPROM.read(addrStatus);
  return a;
}

void clearWifi() {}