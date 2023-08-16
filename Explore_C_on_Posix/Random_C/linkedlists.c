#include <stdio.h>
#include <stdlib.h>
#include <string.h>



typedef struct island
{
  char *name;
  char *opens;
  char*closes;
  struct island *next;
}island;

void display (island *start)
{
  island *i = start;
  for (; i != NULL; i= i ->next)
    printf("Name : %s open from: %s to: %s\n",i -> name,i -> opens ,i -> closes);
}

island* create (char *name)
{
  island *i = malloc(sizeof(island));
  i -> name = strdup(name);
  i -> opens = "09:00";
  i -> closes = "17:00";
  i -> next = NULL;
  return i;

}

void release (island *start)
{
  island *i = start;
  island *next = NULL;
  for (; i!= NULL; i = next)
  {
    next = i ->next;
    free(i ->name);
    free(i);
  }
}



int main ()
{
  island amity = {"Amity","09:00","17:00",NULL};
  island craggy = {"Craggy","09:00","17:00",NULL};
  island isla = {"Isla","09:00","17:00",NULL};
  island shutter = {"Shutter","09:00","17:00",NULL};

  amity.next = &craggy;
  craggy.next = &isla;
  isla.next = &shutter;

  //insertion of a new island between isla and shutter named skull
  island skull = {"Skull","09:00","17:00",NULL};
  isla.next = &skull;
  skull.next = &shutter;

  display(&amity);

  char name [80];
  fgets (name,80,stdin);
  island *p_0 = create(name);
  
  fgets (name,80,stdin);
  island *p_1 = create (name);
  p_0 -> next = p_1;

  display(p_0);

  island *start = NULL;
  island *i = NULL;
  island *next = NULL;
  
  for (; fgets(name,80,stdin) != NULL; i = next)
  {
    next = create(name);
    if (start == NULL)
      start = next;
    if (i!=NULL)
      i ->next = next;
  }
  display(start);


  display (start);
  release(start);
  






}

