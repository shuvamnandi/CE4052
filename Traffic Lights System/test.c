#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "timeout.h"

void main(void)
{
  pthread_t thread1;
  int T1ret;
  int time = 5;
  printf("Jello\n");
  
  printf("Creating timer thread for 5 seconds\n");
  T1ret = pthread_create(&thread1, NULL, start_countdown, time);
  printf("Waiting for timer thread to join\n");
  pthread_join(thread1, NULL);
  printf("T1 returned : %d", T1ret);
  //return 1;
  
}
