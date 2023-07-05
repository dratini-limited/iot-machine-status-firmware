#include "client_mqtt.h"

WiFiClient wifiClient;

const char broker[] = "103.11.198.200";
int        port     = 1883;
const char onOffDeviceTopic[]  = "on-off-device";
const char alertTopic[]  = "alert";
int count = 0;

void callback(char* topic, byte* payload, unsigned int length) {
  String myString = String((char*)payload);
  
  JSONVar myObject = JSON.parse(myString);
  Serial.println(myString);
  Serial.println(topic);
  Serial.println(myObject);

  if (strcmp(topic, "on-off-device") == 0 && strcmp(myObject["UniDeviceCode"], DEVICE_CODE) == 0) {
    int stt = LOW;
    if (myObject["Status"]) {
      stt = HIGH;
    }
    digitalWrite(12, stt);
    delay(500);
    digitalWrite(12, LOW);
    sendOnOffStatus(false);
  } else if (strcmp(topic, "alert") == 0 && strcmp(myObject["UniDeviceCode"], DEVICE_CODE) == 0) {
    Serial.println("alert called");
    alertTone();
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
    count++;
    if (count >= 20) {
      wifiFailSignal();
      break;
    }
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  WiFi.setAutoReconnect(true);
  WiFi.persistent(true);

  setupMQTTClient();
  if (count < 20) {
    wifiConnectedSignal();
  }
}

void sendOnOffStatus(bool status) {
  JSONVar myObject;
  myObject["UniDeviceCode"] = DEVICE_CODE;
  myObject["Status"] = status;
  String jsonString = JSON.stringify(myObject);
  char buf[100];
  jsonString.toCharArray(buf, 100);
  Serial.print("Send to on off status: ");
  Serial.println(jsonString);
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

  Serial.print("Subscribing to topic: ");
  Serial.println(alertTopic);
  Serial.println();

  client.subscribe(alertTopic);
}

void handleWifiClient() {
  client.loop();
}