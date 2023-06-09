#include "access_point.h"
#include "uni_eeprom.h"
#include "client_mqtt.h"
#include "buzzer.h"

int status = 0;
int doneInit = 0;
const unsigned char Passive_buzzer = BUZZER_PIN;
const unsigned char State_Input_Pin = 14;
const unsigned char Button_Pin = 16;
const unsigned char Output_Pin = 12;
int val = 0;
int buttonState = 1;
int lastButtonState = 1;
int lastInputState = 1;
unsigned long buttonPressTime;
int hold = 0;


// char* ssid1 = "Dratini_company";
// char* password = "hyak210522";
// extern PubSubClient mqttClient;

void setup() {
  Serial.begin(115200);
  setupEeprom();
  pinMode(Passive_buzzer, OUTPUT);
  pinMode(Output_Pin, OUTPUT);
  pinMode(State_Input_Pin, OUTPUT);
  pinMode(Button_Pin, INPUT);
  // setWifi(ssid1, password);
  digitalWrite(State_Input_Pin, HIGH);
  delay(1000);
  pinMode(State_Input_Pin, INPUT);

  Serial.println();
  Serial.println(DEVICE_CODE);
  Serial.println(DEVICE_PASSWORD);

  status = getStatus();
  Serial.println(status);

  int passwordLength = (int)EEPROM.read(ADDR_STATUS + 2);
  Serial.println(passwordLength);

  if (status == 1) {
    char* password;
    password = getPassword();
    Serial.println(password);

    char* ssid;
    ssid = getSSID();
    Serial.println(ssid);
    setupWifiClient(ssid, password);
  } else {
    setupAccessPoint();
  }
}

void loop() {
  if (status) {
    handleWifiClient();
  } else {
    handleClient();
  }
  val = digitalRead(State_Input_Pin);
  buttonState = digitalRead(Button_Pin);

  // Serial.print(val);
  // Serial.print("-");
  // Serial.println(lastInputState);
  if (val == 0) {
    openingSignal();
    delay(1000);
  }
  if (lastInputState != val) {
    lastInputState = val;
    if (val == 0) {
      sendOnOffStatus(true);
    } else {
      sendOnOffStatus(false);
    }
    delay(1000);
  }

  if (buttonState != lastButtonState) {
    if (buttonState == 0) {
      buttonPressTime = millis();
      hold = 1;
    } else {
      hold = 0;
    }
  }

  lastButtonState = buttonState;
  if (hold && millis() - buttonPressTime > 5000) {
    hold = 0;
    Serial.println("Clearing wifi");
    bool result = clearWifi();
    Serial.println(result);
    delay(2000);
    ESP.restart();
  }
}