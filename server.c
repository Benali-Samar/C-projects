#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/ipc.h>
#include<sys/types.h>
#include<string.h>
#include<sys/shm.h>


#define SIZE 40

int main()
{

	int shmID;
	char *shmptr, *temp;
	key_t key = 2108;
	char *text="Hello shared";


	//Creat  the shared memo
	shmID = shmget(key,SIZE, IPC_CREAT|0666);
	if (shmID <0)
	{
		printf("Server can't creat the shared memo, EROOR. \n");
		exit(0);
	}

	//Attach the @
	shmptr = shmat(shmID, NULL, 0);
	if(shmptr == (char *) -1)
	{
		printf("Server can't attach the shared memo, ERROR. \n");
	}

	//Writing the shared memo
	temp= shmptr;
	int len = strlen(text);
	for(int i=0;i<len; i++)
	{
		*temp = text [i];
		temp++;
	}


	//Put terminating char for client
	*temp = '%';

	//Make the server wait for client response
	while (*shmptr != '#')
	{
		sleep(1);
	}

	//Detach the @
	shmdt(shmptr);

	//Delete the shared memo
	shmctl(shmID, IPC_RMID,NULL);
	return 0;
}
