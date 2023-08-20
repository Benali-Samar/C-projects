#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

/*
*
*Just a hello world thread program, that creates a thread to write that message and then dies.
*/


void *thread(void *data)
{
	while(1)
	{
		printf("Hello world from thread (the real one not the app :P )\n");
		sleep(1);
	}
	return NULL;
}

int main (void)
{
	pthread_t th;
	printf("This is the main programm\n");
	pthread_create(&th, NULL, thread, NULL);
	sleep(5);
	return 0;
}
