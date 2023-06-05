#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>


// execvp example: Execute a commande with execvp passing by the arguments commands
// with its parametres, example : ./execvp ls -l Documents
//	int main(int argc, char *argv[]) {
// 	argv++;
//	return execvp(argv[0] , argv);
//	}


//------execv() VS execvp():-------
//Both of them do the same functionality of the family exec*, but the only difference is that
//execv; requires the full path of the executable file and an array of string arguments.
//Unlike execvp; that allows you to specify the executable file using only its name and the array of string arguments.


//A fork system call is called than we use execv() to make the child process runs the ls program,
//In the child process, the execv() system call is used to replace the child process
// image with the "ls" program image.
//Meanwhile, the parent process continues executing and waits for the child process to
//finish executing using the 'wait(NULL)' system call.

int main()
{
	int f = fork();
	char * argv[] = {"ls" , "." , NULL};
	switch (f)
	{
	case -1:
		printf("Error while forking!\n");
		exit(EXIT_FAILURE);
	case 0:
		execv("/usr/bin/ls" , argv);
		puts("Problem: it shouldn't be executed!\n");
		exit(EXIT_FAILURE);
	default:
		printf("This is the parent %d, my parent is %d.\n", getpid(), getppid());
		printf("My child is %d.\n", f);
		wait(NULL);
		printf("My child is dead. \n");
		break ;
	}

	return 0;
}


//A simplified diagram to present the described code in background:

//       +-----------------------+
//       |       Parent          |
//       |   Process (PID: P)    |
//       +-----------------------+
//                 |
//                 | Fork()
//                 |
//       +-----------------------+
//       |       Parent          |
//       |   Process (PID: P)    |
//       |    (Continues)        |
//       +-----------------------+
//                 |
//                 | Child Process
//                 | (PID: C)
//                 | Execv("/usr/bin/ls", argv)
//                 |
//       +-----------------------+
//       |       Child           |
//       |   Process (PID: C)    |
//       |   (Executes ls)       |
//       +-----------------------+
