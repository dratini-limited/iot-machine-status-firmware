#ifndef UNI_EEPROM_H
#define UNI_EEPROM_H

#include <EEPROM.h>

void setupEeprom();
void setWifi(char* ssid, char* password);
char* getSSID();
char* getPassword();
char getStatus();
void clearWifi();

#endif