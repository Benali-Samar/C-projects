#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>


// execvp example: Execute a commande with execvp passing by the arguments commands
// with its parametres, example : ./execvp ls -l Documents
//	int main(int argc, char *argv[]) {
// 	argv++;
//	return execvp(argv[0] , argv);
//	}


//A fork system call is called than we use execv() to make the child process runs the vim program
//but it won't because the argv is wrong.
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
