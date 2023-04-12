#ifndef ACCESS_POINT_H
#define ACCESS_POINT_H

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include "uni_eeprom.h"

#ifndef APSSID
#define APSSID "UNI_VLXX"
#endif

void setupAccessPoint();
void handleClient();

#endif