#ifndef UNI_EEPROM_H
#define UNI_EEPROM_H

#include <EEPROM.h>

#define ADDR_SSID 0
#define ADDR_PASSWORD 31
#define ADDR_STATUS 52

void setupEeprom();
bool setWifi(char* ssid, char* password);
char* getSSID();
char* getPassword();
int getStatus();
void clearWifi();

#endif