#include <stdio.h>

//Simple code that reads from a text file and display the content to the sdout.

int main (int argc, char **argv)
{
	FILE *fp;
	char buff[255];

	fp= fopen("test.txt", "r");
	fgets(buff,255,fp);
	printf("%s\n", buff);
	fclose(fp);

	return 0;
}
