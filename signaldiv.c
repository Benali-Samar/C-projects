#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
// for the contexte restitution
#include <setjmp.h>


int x, y, z;
sigjmp_buf env;

void manager (int number)
{
	if (number == SIGFPE)
	{
		printf("Division with zero is detected...\n");
		printf("Enter a non zero number: ");
		scanf("%d", &y);

		//Execution contexte restutition (return value)
		siglongjmp(env,1);
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

	sigsetjmp (env, 1); //Contexte registration

	z= x / y;
	printf("%d/%d = %d\n", x, y, z);
	return 0;
}
