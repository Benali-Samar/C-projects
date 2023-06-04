#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//This code assign a new envirenmental variable with "putenv" and "setenv" functions that it is allocated with malloc.
//setenv(): This function sets the value of an environmental variable or creates a new one if it doesn't exist.
//          If the variable already exists, the function updates its value.
//putenv(): This function sets the value of an environmental variable or creates a new one if it doesn't exist. However,unlike setenv,
//          if the variable already exists, the function replaces its value without updating the value of any other copies of the variable.


int main(void)
{
  char *path , *home , *newpath , *assign;


  path = getenv("PATH");
  home = getenv("HOME");
  printf ("Old PATH : %s\n And HOME : %s\n", path, home);

  assign = malloc((6 + strlen (path) + strlen (home)) * sizeof(char));
  // 6 is the length of ':' , "/bin" et '\0'

  sprintf(assign , "PATH=%s:%s/bin" , path , home);

  //putenv(assign); for creating a new envir var
  setenv("PATH", assign, 1); // 1 for ecrase the old one

  free(assign);
  assign = NULL;

  newpath = getenv("PATH");
  printf ("Newpath PATH : %s\n", newpath);
  return 0;
}
