#include "uni_eeprom.h"


int addrSsid = ADDR_SSID;       // 0->30
int addrPassword = ADDR_PASSWORD;  // 31-51
int addrStatus = ADDR_STATUS;

void setupEeprom() {
  EEPROM.begin(512);
}

bool setWifi(char* ssid, char* password) {
  int ssidLength = strlen(ssid);
  int passwordLength = strlen(password);

  EEPROM.write(addrStatus, 1);
  EEPROM.write(addrStatus + 1, ssidLength);
  EEPROM.write(addrStatus + 2, passwordLength);

  for (int i = 0; i < ssidLength; i++) {
    EEPROM.write(addrSsid + i, ssid[i]);
  }

  for (int i = 0; i < passwordLength; i++) {
    EEPROM.write(addrPassword + i, password[i]);
  }

  if (EEPROM.commit()) {
    return true;
  } else {
    return false;
  }
}

char* getSSID() {
  int ssidLength = (int)EEPROM.read(addrStatus + 1);
  char str[ssidLength];
  for (int i = 0; i < ssidLength; i++) {
    str[i] = (char)EEPROM.read(addrSsid + i);
  }
  str[ssidLength] = '\0';
  char *v = new char[ssidLength];
  strcpy(v, str);
  return v;
}

char* getPassword() {
  int passwordLength = (int)EEPROM.read(addrStatus + 2);
  char str[passwordLength];
  for (int i = 0; i < passwordLength; i++) {
    str[i] = (char)EEPROM.read(addrPassword + i);
  }
  str[passwordLength] = '\0';
  char *v = new char[passwordLength];
  strcpy(v, str);
  return v;
}

int getStatus() {
  int a = (int)EEPROM.read(addrStatus);
  return a;
}

void clearWifi() {}