#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>

#define SIZE 256

int main ()
{
	pid_t pid_child;
	int piped [2];
	unsigned char bufferR [SIZE], bufferW [SIZE];

	puts("Pipe Creation");
	if( pipe (piped) != 0) {
		printf("Error in pipe\n");
		exit(1);
	}

	pid_child = fork ();
	switch (pid_child) {
	case -1:
		printf("Fork Error \n");
		exit(2);
		break ;
	case 0:
		printf("Child: Closing the entry pipe door.\n");
		close (piped [1]);
		printf("Reading pipe.\n");
		read(piped[0], bufferR, SIZE);
		printf("The child (%d) has red: '%s'\n", getpid(), bufferR);
		close(piped[0]);
		break ;
	default:
		printf("Parent: closing the exit pipe door.\n");
		close (piped[0]);
		sprintf((char * restrict) bufferW, "Hello this is the parent process (%d) sending a message to the child.", getpid());
		sleep(2);
		write (piped[1], bufferW, strlen((const char*) bufferW) + 1);
		wait (NULL);
		printf("Child process finished.\n");
		close (piped[1]);
		break ;
	}

	return 0;
}
