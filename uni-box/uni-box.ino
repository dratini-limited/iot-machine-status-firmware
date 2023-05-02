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

// char *ssid1 = "Dratini_company";
// char *password = "hyak210522";
// extern PubSubClient mqttClient;

void buzzerSignal() {
  tone(Passive_buzzer, NOTE_AS4, 500);
  delay(1000);
  tone(Passive_buzzer, NOTE_FS5, 500);
  delay(1000);
  tone(Passive_buzzer, NOTE_CS6, 500);
  delay(1000);
  noTone(Passive_buzzer);
  delay(1000);
}

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
  buzzerSignal();
  pinMode(State_Input_Pin, INPUT);

  Serial.println();

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

  Serial.println(val);

  if (lastInputState != val) {
    val = lastInputState;
    if (val == 0) {
      sendOnOffStatus(false);
    } else {
      sendOnOffStatus(true);
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
    bool result = clearWifi();
    Serial.println(result);
    delay(2000);
    ESP.restart();
  }
}