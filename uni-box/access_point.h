#ifndef ACCESS_POINT_H
#define ACCESS_POINT_H

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include "uni_eeprom.h"
#include "buzzer.h"

#define DEVICE_CODE "KAMUI"
#define APSSID "UNI_KAMUI"
#define DEVICE_PASSWORD "KAMUI123"

void setupAccessPoint();
void handleClient();
void setupMQTTClient();

#endif