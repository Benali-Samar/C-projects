#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/ipc.h>
#include<sys/types.h>
#include<string.h>
#include<sys/shm.h>


#define SIZE 40



int main ()
{
	int shmID;
	char *shmptr, *temp;
	key_t key = 2108;

	//Ask for shared memo
	shmID = shmget(key, SIZE, 0666);
	if  (shmID <0)
	{
		printf("Client can't ask for shared memo, ERROR. \n");
		exit(0);
	}


	//Attach the @
	shmptr = shmat(shmID, NULL, 0);
	if (shmptr == (char*) -1)
	{
		printf("Client can't attach the address, ERROR/\n");
		exit(0);
	}

	//Read data
	temp=shmptr;
	while(*temp != '%')
	{
		printf ("%c", *temp);
		temp++;
	}

	//Tell the server that is done
	*shmptr = '#';


	//Detach
	shmdt(shmptr);

	return 0;



}
