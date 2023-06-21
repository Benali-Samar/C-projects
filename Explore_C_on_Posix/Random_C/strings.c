#include <stdio.h>
#include <string.h>


//this is eaual to:
// char * tracks[]= {"....","......","......"}; ==> it is an array of pointers literally
char tracks[][80]=
{
	"I left my heart in harvard med school",
	"Newark, Newark - a wonderfull town",
	"Dancing with a dork",
	"From here to maternity",
	"the girl from Iwo Jima",
};

void find_track(char search_for[])
{
	int i;
	for (i = 0; i < 5; i++)
	{
		if (strstr(tracks[i],search_for))
			printf("Track %i: '%s'\n", i , tracks[i]);
	}
}

//printf the searched string backwards
void print_reverse(char *s)
{
	size_t len = strlen(s);
	char *t = s + len - 1;
	while( t >= s)
	{
		printf("%c", *t);
		t = t - 1;
	}
	puts("");
}


int main()
{
	char search_for[80];
	printf("Search for: ");
	fgets(search_for,sizeof(search_for), stdin);
	//we remove the '\n' given by fgets by default after entering the string and replace it with '\0'
	search_for[strcspn(search_for, "\n")] = '\0';
	find_track(search_for);
	print_reverse(search_for);

	return 0;
}
