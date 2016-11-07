#include "buzzer.h"

void buzzer_off() {
  softToneWrite(BUZZER, 0);
}

void buzzer_on(int freq) {
  softToneWrite(BUZZER, freq);
}

void buzzer_1Hz() {
  softToneWrite(BUZZER, 1);
}

void buzzer_2Hz() {
  softToneWrite(BUZZER, 2);
}

void buzzer_set_up() {
  //wiringPiSetup();
  softToneCreate(BUZZER);
}
