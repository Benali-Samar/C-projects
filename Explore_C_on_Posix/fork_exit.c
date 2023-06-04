#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/types.h>
#include <sys/wait.h>


//The fork used with two childs .
void exit_child(char *name)
{
	printf("%s: %d. My parent is %d\n" , name , getpid(), getppid());
	srand(getpid());
	int delay = (rand () % 10) +1 ;
	printf("%s: I 'll sleep for %d seconds.\n", name , delay);
	sleep(delay);
	printf("%s: I slep for %d seconds.\n" , name , delay);
}


int main (void)
{
	int f , ff , fff;
	f = fork();
	time_t t1 , t2;
	switch (f)
	{
	case -1:
		printf("This is the parent %d, Error while forking!\n" , getpid());
		break;
	case 0:
		exit_child("First Child");
		break ;
	default:
		printf("This is the parent %d, My parent is %d\n", getpid(), getppid());
		printf("The PID of my child is %d\n", f);
		printf("I'll start a second child\n");


	ff= fork();
	switch(ff)
	{
	case -1:
		printf("This is the parent %d. Error while forking!\n", getpid());
		break;
	case 0:
		exit_child("Second child");
		break;
	default:
		t1 = time(NULL);
		fff = wait(NULL);
		fff = wait(NULL);
		t2 = time(NULL);
		printf("My most slow child %d is dead after %ld seconds.\n", fff, t2 - t1);
		break ;
	}
	break;
	}
	return 0;
}
