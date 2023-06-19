#include <stdio.h>

int main (int argc, char **argv)
{
	int d= 2;
	printf("Welcome here is the bugy prog\n");
	//scanf("%d",d); here is the bug , to correct place it with :
	scanf("%d", &d);

	printf("You gave %d\n", d);
	return 0;
}
