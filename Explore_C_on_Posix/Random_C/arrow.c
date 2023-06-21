#include <stdio.h>

// with struct

struct Movie_info
{
	char *name;
	char *ACC;
};

// with union
union movie_info
{
        int id;
        float net_val;
};


int main () 
{
	struct Movie_info* M;
	M = (struct Movie_info*)
		malloc(sizeof(struct Movie_info));

	union movie_info* m;
        m = (union movie_info*)
                malloc(sizeof(union movie_info));


	M -> name = "Inside out 2";
	M -> ACC = "To watch soon";

	m -> id = 01;
	m -> net_val = 125.45;
	printf("ID : %d \n", m -> id);
	printf("NET VAL : %.lf \n", m -> net_val);


	printf("Movie Infor: \n");
	printf("Name : %s \n", M->name);
	printf("ACC : %s \n", M-> ACC);
	return 0;
}


