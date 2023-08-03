//Creating a named pipe writes a msg to it using standard I/O functions and then removes it.

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>


int main (void)
{

	int fd;
	FILE *fp;
	char *filename ="/tmp/fifo.txt";

	if (mkfifo(filename, 0644) != 0)
	{
		printf("Error while creating FIFO\n");
		exit(1);
	}

	fd = open (filename, O_WRONLY);
	fp = fdopen(fd, "w");
	fprintf(fp, "Oy Oy Oy! \n");
	unlink(filename);
	return 0;
}
