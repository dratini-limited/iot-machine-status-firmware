#ifndef CLIENT_MQTT_H
#define CLIENT_MQTT_H

#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <Arduino_JSON.h>
#include "access_point.h"
#include "buzzer.h"

void setupWifiClient(char* ssid, char* password);
void handleWifiClient();
void setupMQTTClient();
void sendOnOffStatus(bool status);

#endif