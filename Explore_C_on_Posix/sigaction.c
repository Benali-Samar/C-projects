//sigaction  function simple usecase
//Sigaction is more modern and recommended of handling signals, you can specify additional flags and options,
// such as specifying a mask of blocked signals during the signal handler's execution.

//-------------synthax------------------
//
//int sigaction(int signum, const struct sigaction *act, struct sigaction *oldact);
//
//---------------------------------------



#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void manager (int number) {
  printf ("CTRL-C detected...\n");
  exit (0);
}

int main (void) {
  struct sigaction act;
  //Set the sa struct
  act.sa_handler = manager;
  //Clear the sa struct
  sigemptyset (&act.sa_mask);
  // No additional flags
  act.sa_flags = 0;

 // Install the signal handler
  if (sigaction (SIGINT, &act, NULL) != 0) {
    perror ("sigaction");
    exit (1);
  }

// simulate a long-running process
  while (1) {
    printf ("Yo! ...\n");
    sleep (1);
  }

  return 0;
}
