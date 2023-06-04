#include <stdio.h>

// This prog uses an external envirement variable and displays it to the screen using puts.

int main (int argc, char *argv[] , char *envp[])
{
	int i;
	for (i=0; envp[i]!=NULL ; i++)
	{
		puts(envp[i]);
	}
	return 0;
}
