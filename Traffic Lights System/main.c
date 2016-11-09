#include <pthread.h>
#include <signal.h>
#include "led.h"
#include "buzzer.h"
#include "timeout.h"

#define BUTTON 14
volatile sig_atomic_t flag = 0;

void set_up() {
  wiringPiSetup();
  led_set_up();
  buzzer_set_up();
  pinMode(BUTTON, INPUT);
}

void handle_keyboard_interrupt(int sig) {
  flag = 1;
}

void state_initialise(void);
void state_red_on(void);
void state_green_on(void);
void state_green_blink_at_1Hz(void);
void state_green_blink_at_2Hz(void);
void state_yellow_on(void);
void (*state)(void) = state_initialise;

int timeout(int time) {
  pthread_t thread1;
  int T1ret;
  T1ret = pthread_create(&thread1, NULL, start_timer, time);
  pthread_join(thread1, NULL);
  if(T1ret == 0) 
    return 1;
  else
    return 0;
}

void state_initialise(void) {
  led_on(YELLOW);
  led_on(RED);
  led_on(GREEN);
  buzzer_on(500);
  if(timeout(1) == 1) {
    led_off(YELLOW);
    led_off(RED);
    led_off(GREEN);
    buzzer_off();
    delay(50);
    state = &state_red_on;
  }
}

void state_red_on(void) {
  led_on(RED);
  while(digitalRead(BUTTON) == LOW) {
    if(flag) {
      return ;
    }
  }
  if(timeout(2) == 1) {
    led_off(RED);
    state = &state_green_on;
  }
}

void state_green_on(void) {
  led_on(GREEN);
  if(timeout(5) == 1) {
    state =  &state_green_blink_at_1Hz;
  }
}

void state_green_blink_at_1Hz(void) {
  led_on_freq(GREEN, 1);
  buzzer_1Hz();
  if(timeout(5) == 1) {
    state = &state_green_blink_at_2Hz;
  }
}

void state_green_blink_at_2Hz(void) {
  led_on_freq(GREEN, 2);
  buzzer_2Hz();
  if(timeout(5) == 1) {
    led_off(GREEN);
    buzzer_off();
    state = &state_yellow_on;
  }
}

void state_yellow_on(void) {
  led_on(YELLOW);
  buzzer_on(500);
  if(timeout(2) == 1) {
    led_off(YELLOW);
    buzzer_off();
    state = &state_red_on;
  }
}

int main() {
  set_up();
  signal(SIGINT, handle_keyboard_interrupt);
  while(1) {
    (*state)();
    if(flag) {
      led_off(RED);
      led_off(GREEN);
      led_off(YELLOW);
      flag = 0;
      return 0;
    }
  }
  return 1;
}

