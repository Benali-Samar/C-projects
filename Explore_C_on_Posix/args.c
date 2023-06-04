#include <stdio.h>
#include <stdlib.h>

//This prog converts the number passed by the arguments to an int or a float.
// the arguments are passed by the command line to the main:
// argc = is the arguments counter and it starts with 0 is the name of the program itself(exp : ./args)
// argv[] = is the array of arguments passed to the program.
// strtol and strtof : two functions to convert to int(strtol) and float(strtof).
int main ( int argc, char *argv[] )
{
	if (argc <2 ) 
	{
		printf("You should put a number as a parametre.\n");
		exit(1);
	}

	char *endptr;
	long entier;
	float reel;
	int i;

	for (i=1;i< argc; i++)
	{
		entier = strtol(argv[i], &endptr, 10 );
		if (*endptr == '\0')
		{
			printf("You gave an integer :%ld. \n", entier);
			continue;
		}

		reel= strtof (argv[i], &endptr);
		if (*endptr == '\0')
		{
			printf(" You gave a reel number: %5.2f.\n", reel);
			continue;
		}
		printf("You gave a wrong number '%s'.\n" , argv[i]);
	}
	return 0;
}
