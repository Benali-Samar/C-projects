#include <stdio.h>
#include <stdlib.h>

//This code uses "getenv" function that takes an enviremental variable as a parametre and returns its content, like HOME or PATH enviremental variables.

int main (int argc, char *argv[])
{
	char *val;
	int i;
	for ( i=1 ; i < argc ; i++)
	{
		val = getenv(argv[i]);
		if (val == NULL)
		{
			printf("%s is not defined as an enviremenetal variabl. \n", argv[i]);
		}
		else
		{
			printf("%s has : '%s'\n",argv[i], val);
		}
	}
	return 0;
}
