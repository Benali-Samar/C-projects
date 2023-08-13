#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int x, y, z;

void manager (int number)
{
	if (number == SIGFPE)
	{
		printf("Division with zero is detected...\n");
		exit(1);
	}
}

int main(void)
{
	struct sigaction act;
	act.sa_handler = manager;
	sigemptyset(&act.sa_mask);
	act.sa_flags = 0;

	if (sigaction ( SIGFPE, &act, NULL) != 0)
	{
		perror ("sigaction");
		exit(1);
	}
	printf("Enter two numbers x and y : \n");
	scanf("%d %d", &x, &y);
	z= x / y;
	printf("%d/%d = %d\n", x, y, z);
	return 0;
}
