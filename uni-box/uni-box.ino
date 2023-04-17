#include "access_point.h"
#include "uni_eeprom.h"
#include "client_mqtt.h"
#include "buzzer.h"

int status = 0;
int doneInit = 0;
const unsigned char Passive_buzzer = BUZZER_PIN;
const unsigned char State_Input_Pin = 14;
const unsigned char Button_Pin = 16;
int val = 0;
int buttonState = 1;
int lastButtonState = 1;
unsigned long buttonPressTime;
int hold = 0;

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
  pinMode(State_Input_Pin, INPUT);
  pinMode(Button_Pin, INPUT);
  delay(1000);
  buzzerSignal();

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
    delay(3000);
    ESP.restart();
  }
}
