#include <stdio.h>
#include <stdlib.h>
#include <string.h>



// A simple usage of a functions pointers for learning purpose

int NUM_ADS = 4;
char *ADS[] = {
   "Black clover: Fantasy,magic, shonen", 
   "Jusjutsu kaisen: magic,demons,shonen",
   "Demon slayer: Demons,fights", 
   "Heavenly delusion: fights,science ,superpower"
  };

int shonen_or_demons(char *s)
{
  return strstr(s,"shoen") || strstr(s,"demons");
}

int fight_and_superpower (char *s)
{
  return strstr(s,"fights") && strstr(s,"superpower");
}



void find( int (*match)(char*))
{
  int i;
  puts("Search resilts:");
  puts("-----------------------------");
  for (i =0; i < NUM_ADS; i++)
  {
    if (match(ADS[i]))
      printf("%s\n",ADS[i]);
  }
  puts("------------------------------");
}






int main ()
{
  
find(shonen_or_demons); 
find(fight_and_superpower);
  
  return 0;
}
