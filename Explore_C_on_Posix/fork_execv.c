#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>


//A fork system call is called than we use execv() to make the child process runs the vim program ...
// ----- TO continuuueee! ----
int main()
{
	int f = fork();
	char * argv[] = {"vim" , "file.c" , "file.h" , NULL};
	switch (f)
	{
	case -1:
		printf("Error while forking!\n");
		break;
	case 0:
		execv("/usr/bin/vim" , argv);
		puts("Problem: it shouldn't be executed!\n");
		break;
	default:
		printf("This is the parent %d, my parent is %d.\n", getpid(), getppid());
		printf("My child is %d.\n", f);
		wait(NULL);
		printf("My child is dead. \n");
		break ;
	}

	return 0;
}
