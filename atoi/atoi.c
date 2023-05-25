#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



int c_atoi(const char *str)
{

	//Initialisation and declaration
	int i;
	int sign;
	long value;

	i=0;
	sign =1;
	value =0;


	//Treats the spaces and the sign wether negatif or positif
	while(((str[i] <= 13 && str[i] >= 9) || str[i] == 32) && str[i] != '\0')
		i++;

	//Negatif
	if (str[i] =='-')
	{
		sign = -1;
		i++;
	}
	//Positif
	else if (str[i] =='+')
	{
		sign = 1;
		i++;
	}

	//Iterates through all characters of input string
	//and take ASKII character of corresponding digit and sub from '0' to get numerical value
	//and multiply by 10 to shuffle digits left to update running total
	while (str[i] >= 48 && str[i] <= 57 && str[i] != '\0')
	{
		value = value *10 + sign * (str[i] - '0');
		i++;
	}

	return value;
}



int main (int argc, char **argv)
{

	//Test of the real atoi
	//int i;
	//char *s;
	//s= "-1236";
	//i = atoi(s);
	//printf(" i = %d \n",i);


	if(argc==2)
	{
		printf("Your number is %d\n", c_atoi(argv[1]));
		return 0;
	}

	printf("Wrong number of parametres \n");
	return 1;

}
