#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

/*
*Hello world thread program with pthread_join() not sleep()
*/

void *thread(void *data)
{
	for (int i = 0; i < 10 ; i++)
	{
		printf("Hello world from thread (the real one not the app :P )\n");
		sleep(5);
	}
	return NULL;
}

int main (void) // the main thread
{
	pthread_t th;
	printf("This is the main programm\n");
	pthread_create(&th, NULL, thread, NULL); // create the thread
	pthread_join (th, NULL); // waits for it to end and comeback to the main thread
	printf("The child thread has ended.\n");

	return 0;
}
