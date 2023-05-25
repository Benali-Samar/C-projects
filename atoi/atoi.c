#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



int c_atoi(const char *str)
{
	int i;
	int sign;
	long value;
	long prev;

	i=0;
	sign =1;
	value =0;


	while(((str[i] <= 13 && str[i] >= 9) || str[i] == 32) && str[i] != '\0')
		i++;

	if (str[i] =='-')
	{
		sign = -1;
		i++;
	}
	else if (str[i] =='+')
	{
		sign = 1;
		i++;
	}

	while (str[i] >= 48 && str[i] <= 57 && str[i] != '\0')
	{
		prev = value;
		value = value *10 + sign * (str[i] - '0');
		i++;
	}

	return value;
}



int main (int argc, char **argv)
{

	//test of atoi
	int i;
	char *s;
	s= "-1236";
	i = atoi(s);
	printf(" i = %d \n",i);


	if(argc==2)
	{
		printf("Your number is %d\n", c_atoi(argv[1]));
		return 0;
	}

	printf("Wrong number of parametres \n");
	return 1;

}
