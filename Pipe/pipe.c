#include <stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>


int main(void) {
	int pipefds[2];    //creating a pipes
	char buf[5];       // buffer for the reading
	char *p="1234\0";  //explicity added the null character cz while writing it to the buff by pipe it should know the end of the char

	if (pipe(pipefds) == -1){
		perror("pipe");
		exit(EXIT_FAILURE);
	}

	pid_t pid = fork(); // creates child process
	if (pid == 0)
	{
	close(pipefds[0]);
	write (pipefds[1],p,5); //writes p to pipe

	printf("Sending p from child to parent ...\n");
	sleep(2);
	exit (EXIT_SUCCESS);
	}


	if (pid > 0)
	{
	wait (NULL);
	close(pipefds[1]);
	read(pipefds[0],buf,5); //read p from pipe
	close(pipefds[0]);

	printf("Parent recieving p '%s' \n", buf);
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
