#include <pthread.h>
#include <unistd.h>
#include "led.h"
#include "buzzer.h"
#include "timeout.h"

#define BUTTON 14

typedef enum {
  INITIALISE, 
  RED_ON,
  GREEN_ON,
  GREEN_AT_1HZ,
  GREEN_AT_2HZ,
  YELLOW_ON
} traffic_light_states;

void set_up() {
  wiringPiSetup();
  led_set_up();
  buzzer_set_up();
  pinMode(BUTTON, INPUT);
}

void state_initialise(void);
void state_red_on(void);
void state_green_on(void);
void state_green_blink_at_1Hz(void);
void state_green_blink_at_2Hz(void);
void state_yellow_on(void);
void (*state)(void) = state_initialise;

int start_countdown(int time) {
  pthread_t thread1;
  int T1ret;
  T1ret = pthread_create(&thread1, NULL, start_timer, time);
  pthread_join(thread1, NULL);
  return T1ret;
}

void state_initialise(void) {
  led_on(YELLOW);
  led_on(RED);
  led_on(GREEN);
  buzzer_on(500);
  delay(500);
  led_off(YELLOW);
  led_off(RED);
  led_off(GREEN);
  buzzer_off();
  delay(500);
  state = &state_red_on;
}

void state_red_on(void) {
  led_on(RED);
  while(digitalRead(BUTTON) == LOW) {
  }
  if(start_countdown(2) == 0) {
    led_off(RED);
    state = &state_green_on;
  }
}

void state_green_on(void) {
  led_on(GREEN);
  if(start_countdown(5) == 0) {
    //led_off(GREEN);
    state =  &state_green_blink_at_1Hz;
  }
}

void state_green_blink_at_1Hz(void) {
  led_on_freq(GREEN,1);
  buzzer_1Hz();
  if(start_countdown(5) == 0) {
    //led_off(GREEN);
    state = &state_green_blink_at_2Hz;
  }
}

void state_green_blink_at_2Hz(void) {
  led_on_freq(GREEN,2);
  buzzer_2Hz();
  if(start_countdown(5) == 0) {
    led_off(GREEN);
    buzzer_off();
    state = &state_yellow_on;
  }
}

void state_yellow_on(void) {
  led_on(YELLOW);
  buzzer_on(500);
  if(start_countdown(2) == 0) {
    led_off(YELLOW);
    buzzer_off();
    state = &state_red_on;
  }
}

int main() {
  set_up();
  while(1) {
    (*state)();
  }
  return 1;
}

