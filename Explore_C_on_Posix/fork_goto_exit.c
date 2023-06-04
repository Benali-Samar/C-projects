#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <wait.h>

// This code take the number of childs needs to create and if it finish it goes to the exit with "goto".

int main (int argc, char *argv[])
{
	if (argc != 2)
	{
		printf("You should pass a number in parametres.\n");
		exit(1);
	}

	int number;
	if (sscanf (argv[1], "%d" , &number) != 1)
	{
		printf("Invalid number!\n");
		exit(1);
	}
	pid_t f;
	int i;

	for (i=0 ; i< number ; i++)
	{
		f= fork();
		switch (f)
		{
		case -1:
			printf("This is Parent, Error while forking! \n");
			break ;
		case 0:
			printf("Here is the child %d, My parent is %d\n", getpid(), getppid());
			goto exit_child; //IMPORTANT !!
			break;
		default:
			printf("Here is the parent %d, my parent is %d\n", getpid(), getppid());
			printf("The child's PID is %d\n" , f);
			break;
		}
	}

	for (i=0 ; i<number ; i++)
	{
		wait(NULL);
	}

	return 0; //IMPORTANT !!

	exit_child:
		printf("Child %d is dead. \n", getpid());
}
