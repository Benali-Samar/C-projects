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
	while(1)
	{
	int pipefds[2];    //creating a pipes
	char buf[P_LENGTH +1];       // buffer for the reading
	char p[P_LENGTH + 1 ] ;

	pipe(pipefds);

	pid_t pid = fork(); // creates child process
	if (pid == 0)
	{
	getP(p);
	close(pipefds[0]);
	write (pipefds[1],p, P_LENGTH +1 ); //writes p to pipe

	printf("Sending p from child to parent ...\n");
	sleep(P_WAIT_INTERVAL);
	exit (EXIT_SUCCESS);
	}


	if (pid > 0)
	{
	wait (NULL);
	close(pipefds[1]);
	read(pipefds[0],buf,P_LENGTH + 1); //read p from pipe
	close(pipefds[0]);

	printf("Parent recieving p '%s' \n", buf);
	}
	}
//	printf("Writing p to pipe ... \n");
//	write(pipefds[1],p,5); //it writes the 5  characters to the pipe
//	printf("Done writing \n\n");

//	printf("Reading p from pip ... \n");
//	read(pipefds[0],buf,5); // reads them from the pip  and for displaying using buffer
//	printf("Done reading \n\n");

//	printf("P from pipe : %s \n", buf);

//	printf("Read fd value : %d \n", pipefds[0]);
//	printf("Write fd value : %d \n", pipefds[1]);

	return EXIT_SUCCESS;
}
