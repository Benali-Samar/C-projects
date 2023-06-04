#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

// This code just test the fork() system call that creates a duplication of the existing process.

int main(void)
{
	pid_t f;  // It is an int that has the PID number
	printf("Hello!\n");
	f = fork();
	switch(f)
	{
	case -1:
		printf("This is the parent : %d. Error Fork!\n", getpid());
		break;
	case 0:
		sleep(1);
		printf("This is the child %d. My parent is %d\n.", getpid(), getppid());
		sleep(2);
		printf("This is the child %d. I'm dead.\n", f);
		break;
	default:
		printf("This is the parent process: %d , my parent is %d\n", getpid(), getppid());
		printf("My child process is %d\n", f);
		pid_t ff = wait( NULL);
		printf("My child %d is dead. \n" , ff);
		break;
	}
	return 0;
}

