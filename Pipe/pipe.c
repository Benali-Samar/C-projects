#include <stdio.h>
#include<stdlib.h>
#include<unistd.h>

int main(void) {
	int pipefds[2];    //creating a pipes
	char buf[5];       // buffer for the reading
	char *p="1234\0";  //explicity added the null character cz while writing it to the buff by pipe it should know the end of the char

	if (pipe(pipefds) == -1){
		perror("pipe");
		exit(EXIT_FAILURE);
	}



	printf("Writing p to pipe ... \n");
	write(pipefds[1],p,5); //it writes the 5  characters to the pipe
	printf("Done writing \n\n");

	printf("Reading p from pip ... \n");
	read(pipefds[0],buf,5); // reads them from the pip  and for displaying using buffer
	printf("Done reading \n\n");

	printf("P from pipe : %s \n", buf);

//	printf("Read fd value : %d \n", pipefds[0]);
//	printf("Write fd value : %d \n", pipefds[1]);

	return EXIT_SUCCESS;
}
