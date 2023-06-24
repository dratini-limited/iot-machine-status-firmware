#ifndef ACCESS_POINT_H
#define ACCESS_POINT_H

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include "uni_eeprom.h"
#include "buzzer.h"

#define DEVICE_CODE "YUNO"
#define APSSID "UNI_YUNO"
#define DEVICE_PASSWORD "QAZXSW"

void setupAccessPoint();
void handleClient();
void setupMQTTClient();

#endif