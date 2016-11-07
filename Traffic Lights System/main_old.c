
#include <unistd.h>
#include <wiringPi.h>
#include <softTone.h>
#include <pthread.h>
//#include "timeout.c"

#define YELLOW 0
#define RED 2
#define GREEN 7
#define BUZZER 1
#define BUTTON 14

void main(void) {
  //pthread_t timer_thread;
  int timer;
  set_up();
  initialise();
  led_on(RED);
  buzzer_on(500);
  delay(500);
  buzzer_off();
  printf(digitalRead(BUTTON));
  printf("\n");
  while (digitalRead(BUTTON) == LOW) {
	printf("Button is low \n");
  }
  button_operate();
  printf("Almost there\n");
  //timer_thread(2);
  //timer=pthread_create(&timer_thread, NULL, timer_countdown, 5);
  //pthread_join(timer_thread, NULL);
  printf("Its over now\n");
}


int set_up() {
  wiringPiSetup();
  softToneCreate(BUZZER);
  pinMode(YELLOW, OUTPUT);
  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BUTTON, INPUT);
  softToneCreate(YELLOW);
  softToneCreate(RED);
  softToneCreate(GREEN);
  return 0;
}

int initialise() {
  led_on(YELLOW);
  led_on(RED);
  led_on(GREEN);
  delay(500);
  led_off(YELLOW);
  led_off(RED);
  led_off(GREEN);
  delay(500);
}

void led_on(int pin) {
  digitalWrite(pin, HIGH);
}

void led_off(int pin) {
  digitalWrite(pin, LOW);
}

void led_on_freq(int pin, int frequency) {
  softToneWrite(pin, frequency);
}

void buzzer_on(int frequency) {
  softToneWrite(BUZZER, frequency);
}

void buzzer_off() {
  softToneWrite(BUZZER, 0);
}

void button_operate() {
  delay(2000);
  led_off(RED);
  led_on(GREEN);
}


