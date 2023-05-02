#ifndef ACCESS_POINT_H
#define ACCESS_POINT_H

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include "uni_eeprom.h"

#define DEVICE_CODE "KSLMJH"
#define APSSID "UNI_KSLMJH"

void setupAccessPoint();
void handleClient();
void setupMQTTClient();

#endif