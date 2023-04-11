
int addrSsid = 0;       // 0->30
int addrPassword = 31;  // 31-51
int addrStatus = 52;

void setupEeprom() {
  EEPROM.begin(512);
}

void setWifi(String ssid, String password) {
  int ssidLength = ssid.length();
  int passwordLength = password.length();

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
  byte ssidLength = EEPROM.read(addrStatus + 1);
  char* str = (char*)malloc(sizeof(char) * ssidLength);
  for (int i = 0; i < ssidLength; i++) {
    str[i] = EEPROM.read(addrSsid + i);
  }

  return str;
}

char* getPassword() {
  byte passwordLength = EEPROM.read(addrStatus + 2);
  char* str = (char*)malloc(sizeof(char) * passwordLength);
  for (int i = 0; i < passwordLength; i++) {
    str[i] = EEPROM.read(addrPassword + i);
  }

  return str;
}

byte getStatus() {
  byte status = EEPROM.read(addrStatus);
  return status;
}

void clearWifi() {}