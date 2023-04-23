#include "client_mqtt.h"

WiFiClient wifiClient;

const char broker[] = "ssh.dratini.tech";
int        port     = 1883;
const char onOffDeviceTopic[]  = "on-off-device";

void callback(char* topic, byte* payload, unsigned int length) {
  String myString = String((char*)payload);
  
  JSONVar myObject = JSON.parse(myString);
  Serial.println(topic);
  Serial.println(myObject);

  if (strcmp(topic, "on-off-device") == 0) {
    int stt = LOW;
    if (myObject["Status"]) {
      stt = HIGH;
    }
    digitalWrite(12, stt);
    delay(myObject["Delay"]);
    digitalWrite(12, LOW);
  }
}

PubSubClient client(broker, 1883, callback, wifiClient);

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

  setupMQTTClient();
}

void sendOnOffStatus(bool status) {
  JSONVar myObject;
  myObject["UniDeviceCode"] = DEVICE_CODE;
  myObject["Status"] = status;
  String jsonString = JSON.stringify(myObject);
  char buf[100];
  jsonString.toCharArray(buf, 100);
  Serial.println("Send to on off status");
  client.publish("on-off-status", buf);
}

void setupMQTTClient() {
  Serial.print("Attempting to connect to the MQTT broker: ");
  Serial.println(broker);

  if (client.connect(DEVICE_CODE, "admin", "mMjAeR8xZYZKzzwP")){
    Serial.println("MQTT Connected");
  } else {
    Serial.println("Fail to connect to mqtt");
  }

  Serial.print("Subscribing to topic: ");
  Serial.println(onOffDeviceTopic);
  Serial.println();

  client.subscribe(onOffDeviceTopic);
}

void handleWifiClient() {
  client.loop();
}