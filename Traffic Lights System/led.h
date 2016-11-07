#include <wiringPi.h>
#include <softTone.h>

#define RED 2
#define GREEN 7
#define YELLOW 0 

void led_on(int pin);
void led_off(int pin);
void led_on_freq(int pin, int freq);
void led_set_up();
