#include "led.h"

void led_on(int pin) {
  digitalWrite(pin, HIGH);
}

void led_off(int pin) {
  digitalWrite(pin, LOW);
  softToneWrite(pin, 0);
}

void led_on_freq(int pin, int freq) {
  softToneWrite(pin, freq);
}

void led_set_up() {
 // wiringPiSetup();
  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(YELLOW, OUTPUT);
  softToneCreate(RED);
  softToneCreate(GREEN);
  softToneCreate(YELLOW);
}

