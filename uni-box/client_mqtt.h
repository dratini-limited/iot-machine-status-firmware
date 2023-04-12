#ifndef CLIENT_MQTT_H
#define CLIENT_MQTT_H

#include <ESP8266WiFi.h>

void setupWifiClient(char* ssid, char* password);
void handleWifiClient();

#endif