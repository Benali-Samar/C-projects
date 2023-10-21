#include <stdio.h>
#include <stdlib.h>

void go_south_east(int* lat, int* lon)
{
	*lat -= 1;
	*lon += 1;
}

void skip(char *msg)
{
	puts(msg+6);
}

int main ()
{
	int latitude = 32;
	int longitude = -64;
	//int* addr_of_latitude = &latitude;
	//int* addr_of_longitude = &longitude;

	go_south_east(&latitude, &longitude);

	//printf("latitude is at %p and longitude lives at %p  \n", &latitude, &longitude);
	//printf("The add of latitude is %p and the add of longitude is %p \n", addr_of_latitude, addr_of_longitude);

	//printf("The value stored in latitude is %d\n", *addr_of_latitude);
	//*addr_of_latitude = 50;
	//printf("Now the value of latitude becomes : %d \n", latitude);

	printf("Avast! Now at: [%i, %i]\n", latitude, longitude);

	char msg [] = "Hello lazy shitty, you need to do better!";
	printf("number of codes is %d\n",sizeof(int));
	printf("the msg is : %s\n", msg);
	printf("the msg is stored in %p \n", msg);

	printf("the size of msg is %i\n",sizeof(msg));

	char *msg_from_amy = "Don't call me";
	skip(msg_from_amy);

	int nums[]={1,2,3,4};
	printf("nums is at %p\n", nums);
	printf("nums+1 is at %p\n", nums+1);
	printf("nums 2 %i\n", 2[nums]);

	char food[5];
//	printf("Gimme ur food: \n");
//	scanf("%s", food);
//	printf("your food is: %s\n",food);

	char name[5];
	printf("Gimme ur name\n");
	fgets(name, 5, stdin);
//	gets(name); this is so dangerous it cause buffer overflow attack
	//name[strcspn(name, "\n")] = '\0';
	printf("Your name is %s\n",name);

//	char *s = "some string"; //so basicly with this we've got a segfault error cz it is a char pointer not only an array to prevent this we should make a copy to an array 
//also when : const char *s ="some string" ==> it causes error saying it is in a read only memeory location!
	char s [] ="some sting";
//	s [1] = s [3];
	s[1] = 'a';
	puts(s);

	return 0;
}

//	-----CLARIFICATION----
//So basicly * and & are opposite :
// The & operator just takes the value and tells you where it is stored; the address of it.
// Where the * operator takes the adress of the value and tells you what is stored in there; its content.
// and the * can read the content or write!

