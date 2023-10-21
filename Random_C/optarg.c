//

//Using "getopt()" C library function to parse command line arguments.
//synthaxe : getopt(int argc, char *const argv[], const char *optstring
  //optstring is simply  a list of characters,each representing a single character option.

// 
#include <stdio.h>
#include <unistd.h>

int main (int argc,char *argv[])
{
  char *delevery ="";
  int thick = 0;
  int count;
  char ch;

  while((ch = getopt(argc,argv,"d:ts"))!= EOF)
  {
    switch (ch)
    {
      case 'd':
      delevery = optarg;
      break ;
      case 't':
      thick = 1;
      break;
      case 's':
      puts("Spicy");
      break;
      default:
      fprintf(stderr,"Unknown option: '%s'\n",optarg);
      return 1;
    }
  }
    argc -= optind;
    argv += optind;

    if (thick)
      puts("Thick crust.");

    if (delevery[0])
      printf("To be delevered %s.\n",delevery);

    puts("Ingrediants:");

    for (count = 0; count <argc; count++)
      puts(argv[count]);
    return 0;
  
}

