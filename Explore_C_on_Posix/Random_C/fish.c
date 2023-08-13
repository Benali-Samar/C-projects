#include <stdio.h>
#include <stdlib.h>


struct preferences 
{
  const char *food;
  float exercise_hours;
};

struct fish 
{
  const char *name;
  const char *species;
  int teeth;
  int age;

  struct preferences care;

};

void catalog (struct fish f)
{
  printf("%s is a %s with %i teeth. He is %i\n",f.name,f.species,f.teeth,f.age);
}

void label (struct fish f)
{
  printf("Name : %s \n",f.name);
  printf("species : %s \n",f.species);
  printf("%i years old, %i teeth\n",f.age,f.teeth);
}
int main ()
{
  struct fish snappy = {"Snappy", "piranha", 69, 4,{"Meat",7.5}};
  printf("Name = %s\n", snappy.name);
  printf("snappy likes to eat %s\n",snappy.care.food);
  printf("snappy likes to exercise for %f hours\n",snappy.care.exercise_hours);
  catalog(snappy);
  label(snappy);
}
