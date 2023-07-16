//Simple "system" function usage, system is a function allowing user to excute command through a C code.
// Synthaxe : system(const char* command)

#include <stdio.h>
#include <stdlib.h>


int main()
{
	system ("ps aux | grep init");
	system ("sleep 1");
	return 0;
}
