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
	static int trys = 1;
	if (number == SIGFPE)
	{
		if(trys == 5)
		{
			printf("You already used your trys.\n");
			exit(3);
		}

		printf("Division with zero is detected...\n");
		printf("Enter a non zero number: ");
		scanf("%d", &y);
		trys ++;

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


	int r = sigsetjmp (env, 1); //Contexte registration
	// if r == 0: we reached here normally
	// if r != 0: we jumped in code with (siglongjmp)
	// r value is specified  in the siglongjmp call.

	if (r !=0)
	{
		printf("Try %d of division ... \n", r);
	}

	z= x / y;
	printf("%d/%d = %d\n", x, y, z);
	return 0;
}
