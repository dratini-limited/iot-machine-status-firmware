#include "access_point.h"

const char *ssid = APSSID;
ESP8266WebServer server(80);

void handleRoot() {
  server.send(200, "text/html", "<h1>You are connected</h1>");
}

void handleExternalWifi() {
  String ssid = server.arg("ssid");
  String password = server.arg("password");
  Serial.println(ssid);
  Serial.println(password);
  
  char *ssidChar = new char[ssid.length() + 1];
  strcpy(ssidChar, ssid.c_str());

  char *passChar = new char[password.length() + 1];
  strcpy(passChar, password.c_str());

  setWifi(ssidChar, passChar);
  server.send(200, "text/html", "OK");
}

void setupAccessPoint() {
  Serial.println();
  Serial.print("Configuring access point...");

  WiFi.softAP(ssid);
  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(WiFi.localIP());
  server.on("/", handleRoot);
  server.on("/wifi", handleExternalWifi);
  server.begin();
  Serial.println("HTTP server started");
}

void handleClient() {
  server.handleClient();
}