#include <stdio.h>
#include <stdlib.h>
#include <string.h> //for the strcmp()


// a char** ==> a pointer to an array of strings : a pointer to pointer maybe :/ 

int scores[] = {543,223,32,554,11,3,122};

int compare_score(const void* score_a,const void* score_b)
{
  int a =*(int*)score_a;
  int b =*(int*)score_b;
  return a - b;
}

int compare_score_desc(const void* score_a,const void* score_b)
{
  int a =*(int*)score_a;
  int b =*(int*)score_b;
  return b - a;
}

typedef struct 
{
  int width;
  int height;
} rectangle;

int compare_areas(const void* a ,const void* b)
{
  //convert the pointers to the correct type
  rectangle* ra = (rectangle*)a;
  rectangle* rb = (rectangle*)b;

  //calculate the area
  int area_a = (ra ->width * ra -> height);
  int area_b = (rb ->width * rb -> height);
  
  //the substruction to know whether positive,negative or null
  return area_a - area_b;
}

int compare_names(const void* a ,const void* b)
{
  //A string is a pointer to a char,so the pointers you're given are pointers to pointers ... (i know it is shit -_- )
  char** sa = (char**)a;
  char** sb = (char**)b;
  //the * operator to find the actual string
  return strcmp(*sa,*sb);
}

int compare_areas_desc(const void* a,const void*b)
{
  return compare_areas(b,a);
}

int compare_names_desc( const void* a, const void* b)
{
  return compare_names(a,b);
}


int main()
{
  int i ;
  //This will sort the scores
  //qsort() does not make a sorted array it actually modifies the original array
  qsort(scores, 7, sizeof(int),compare_score_desc);
  puts ("These are the scores in order:");
  for (i =0; i<7;i++)
    printf("Score = %i\n", scores[i]);

  char *names[]= {"Maru","Asta","Rin","Gabimaru"};
  // This will sort the names, and remember an array of names is just an array of char pointers so the size of each item is sizeof(char*) !
  qsort(names,4,  sizeof(char*), compare_names);
  puts("These are the names in order:");
  for(i =0; i<4; i++)
      printf("%s\n", names[i]);

  return 0;
  
}
