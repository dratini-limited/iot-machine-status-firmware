#include "buzzer.h"
#include <Esp.h>

const unsigned char Passive_buzzer = BUZZER_PIN;

void alertTone() {
  for (int i = 0; i < 4; i++) {
    tone(Passive_buzzer, NOTE_G6, 1000);
    delay(200);
    noTone(Passive_buzzer);
    delay(100);
    tone(Passive_buzzer, NOTE_G6, 1000);
    delay(200);
    noTone(Passive_buzzer);
    delay(100);
    tone(Passive_buzzer, NOTE_G6, 1000);
    delay(200);
    noTone(Passive_buzzer);
    delay(100);
  }
  noTone(Passive_buzzer);
  delay(1000);
}

// Beep one time in 2s
void wifiConnectedSignal() {
  tone(Passive_buzzer, NOTE_G6, 1000);
  delay(2000);
  noTone(Passive_buzzer);
  delay(1000);
}

// Beep 2 times with one time in 1s
void wifiFailSignal() {
  tone(Passive_buzzer, NOTE_C5, 1000);
  delay(1000);
  noTone(Passive_buzzer);
  delay(100);
  tone(Passive_buzzer, NOTE_C5, 1000);
  delay(1000);
  noTone(Passive_buzzer);
  delay(1000);
}

// Beep 3 times with each one 500ms
void routerModeSignal() {
  tone(Passive_buzzer, NOTE_CS6, 500);
  delay(500);
  noTone(Passive_buzzer);
  delay(100);
  tone(Passive_buzzer, NOTE_CS6, 500);
  delay(500);
  noTone(Passive_buzzer);
  delay(100);
  tone(Passive_buzzer, NOTE_CS6, 500);
  delay(500);
  noTone(Passive_buzzer);
  delay(100);
  noTone(Passive_buzzer);
  delay(1000);
}