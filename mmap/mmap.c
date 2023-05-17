#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


#define handle_error(msg) do { perror(msg); exit(EXIT_FAILURE);} while(0)

int main (int argc, char *argv[])
{

	char *addr;
	int fd;
	struct stat sb;
	off_t offset, pa_offset;
	size_t len;
	ssize_t s;

	//Define the args number passed by cmdline
	if(argc < 3 || argc > 4){
		fprintf(stderr, "%s file offset [length] \n", argv[0]);
		exit(EXIT_FAILURE);
		}

	//Opens the file passed to the second arg(the first is the name of the program)
	fd = open(argv[1], O_RDONLY);
	if(fd== -1)
		handle_error("Open error");

	//Returns the status of the file descriptor
	if(fstat(fd, &sb) == -1)
		handle_error("fstat");

	//Offset for mmap page allignement
	offset = atoi(argv[2]); //Conversion of the third arg to int
	//Sysconf(_SC_PAGE_SIZE) ==> retrieves the system's page size that represent te memeory allocated
	//Sysconf(_SC_PAGE_SIZE) -1 ==> minus 1 from the page size to ensure that the resulting value is a bitmask( the process of storing data is truly as bits)
	//~ Sysconf(_SC_PAGE_SIZE) -1 ==> the "~" is for the bitwise negation where all the last bits are set to 1
	//& ~ Sysconf(_SC_PAGE_SIZE) -1 ==>  the "&" is to clear bits setted to 0 from the result of (~ Sysconf(_SC_PAGE_SIZE) -1 )
	pa_offset = offset & ~(sysconf(_SC_PAGE_SIZE) - 1 );


	if (offset >= sb.st_size) {
		fprintf(stderr,"Offset is past end of file \n ");
		exit (EXIT_FAILURE);
		}

	//If it can't display bytes past end of file
	  if (argc == 4) {
          	len = atoi(argv[3]);
          	if (offset + len > sb.st_size)
			len = sb.st_size - offset;

           } else {    /* No length arg ==> display to end of file */
             	len = sb.st_size - offset;
           }

	// Use of mmap for mapping the required pages of the file
	   // mmap() parametres explanation:
	   // - NULL : is the address, not specified to allow the system to choose the add
	   // - len + offset - pa_offset : is the length of the mapping in bytes, the total size of the memeory region to map
	   // - PROT_READ : defines the desired memory protection of the mapped region
	   // - MAP_PRIVATE : is the flag to create a private copy-on-write mapping
	   // - fd : the file descriptor of the file to be mapped
	   // - pa_offset : the offset where to start the mapping of the file
	addr = mmap(NULL, len + offset - pa_offset, PROT_READ, MAP_PRIVATE, fd, pa_offset);
	if (addr == MAP_FAILED) {
   		 handle_error("Mmap error\n");
	}

	// Use write to output for the file
	s = write(STDOUT_FILENO, addr + offset - pa_offset, len);
	if (s != len) {
    		handle_error("Write error\n");
    	   	exit(EXIT_FAILURE);
	}

	//Unmap everything and close file
	munmap(addr, len + offset - pa_offset);
	close (fd);

	exit( EXIT_SUCCESS);
}
