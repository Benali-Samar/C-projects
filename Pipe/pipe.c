#include <stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>

#define P_LENGTH 4
#define P_WAIT_INTERVAL 2


//********
//* PIPE usage
//* Child creation using fork ()
//* Read/write the PIN
///********



// continously creates a child process and generates p in it and sends the p to the parent using pipe
void getP(char p[P_LENGTH +1])
{
	srand(getpid() + getppid());
	p[0] = 49 + rand() %7;

	for (int i = 1; i< P_LENGTH; i++)
	{
	p[i] = 48 + rand() % 7;
	}
	p[P_LENGTH] = '\0';
}


int main(void) {

	int pipefds[2];    //creating a pipes
	char buf[P_LENGTH +1];       // buffer for the reading
	char p[P_LENGTH + 1 ] ;

	pipe(pipefds);

	for ( int i =0 ; i<4; i++)
	{

		pid_t pid = fork(); // creates child process
		if (pid == -1)
		{
			perror("fork");
			return 1;
		}
		else if (pid == 0)
		{ // the child process
		getP(p);
		close(pipefds[0]);
		write (pipefds[1],p, P_LENGTH +1 ); //writes p to pipe
		printf("Hello from child process! child PID: %d\n", getpid());

		printf("Sending p from child to parent ...\n");
		sleep(P_WAIT_INTERVAL);
		exit (EXIT_SUCCESS);
		}

	}

	close(pipefds[1]);
	read(pipefds[0],buf,P_LENGTH + 1); //read p from pipe
	close(pipefds[0]);


	for (int i=0;i<4;i++)
	{
		wait(NULL);
	}

	printf("Hello from the parent process! Parent PID: %d\n", getpid());
	printf("Parent recieving p '%s' \n", buf);


	return EXIT_SUCCESS;
}
