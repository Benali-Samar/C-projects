//Signal function simple usecase
//When a signal occurs, the signal function allows you to specify a signal handler.

//--------------------synthax---------------
//
//void (*signal(int signum , void(*handler)(int)))(int);
//
//------------------------------------------


#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void manager (int number) {
  printf ("CTRL-C detected...\n");
  exit (0);
}

int main (void) {
  int a = 0;

  if (signal (SIGINT, manager) == SIG_ERR) {
    perror ("signal");
    exit (1);
  }

  while (1) {
    printf ("%d : Yo! ...\n", a);
    a++;
    sleep (1);
  }

  return 0;
}
