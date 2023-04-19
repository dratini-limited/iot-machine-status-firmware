#include "client_mqtt.h"

void setupWifiClient(char* ssid, char* password) {
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);
  int numNetworks = WiFi.scanNetworks();
  for (int i = 0; i < numNetworks; i++) {
    if (WiFi.SSID(i) == ssid) {
      WiFi.begin(WiFi.SSID(i), password, WiFi.channel(i), WiFi.BSSID(i), true);
      break;
    }
  }

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  WiFi.setAutoReconnect(true);
  WiFi.persistent(true);
}

void setupMQTTClient() {
}

void handleWifiClient() {
}