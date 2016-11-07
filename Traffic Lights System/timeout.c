// timeout.c
// The program use select() system call to perform a timeout
// it also monitors the stdin for input - which effectively overwrite the timeout
//To compile:  gcc -o timer timer.c

#include <unistd.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/select.h>
#include <stdio.h> /* for printf */
#include <stdlib.h> /* for atoi() */

int *start_timer(int time)
{ int n, duration = 5;
  fd_set input;
  struct timeval timeout;

  duration = time;
  printf("Timeout in  %d sec\n", duration);

  /* Initialize the input set */
  FD_ZERO(&input);
  FD_SET(STDIN_FILENO, &input);   // use stdin file descriptor

  /* Initialize the timeout structure */
  timeout.tv_sec = duration;
  timeout.tv_usec = 0;

  //printf("call select()....\n");

  /* Do the select, will typically sleep based on mask returned by poll method, and trigger again when queue wakeup */ 
  n = select(FD_SETSIZE, &input, NULL, NULL, &timeout);
 
  /* See if there was an error */
  if (n < 0)
     perror("Timeout failed");
  else
  if (n == 0)
     puts("TIMEOUT");
  else /* n >0, we have input, from which source? */
       printf("Key pressed - Timeout terminated\n");
}
