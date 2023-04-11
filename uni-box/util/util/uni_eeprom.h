#ifndef UNI_EEPROM_H
#define UNI_EEPROM_H

#include <EEPROM.h>

void setupEeprom();
void setWifi(String ssid, String password);
char* getSSID();
char* getPassword();
byte getStatus();
void clearWifi();

#endif