/*
*   Have you wondred someday how 'printf()' can accept all type of arguments ?
*     like printf("hello"); or printf("%i",a); or pintf("%s","how?");
*     it is literally implemented like this :
*         int printf (const char * arg, ...);
*         So those "..." are the unknown args that will be passed to the function.
*   Weeell,yea there is special function used there that can accept an unknown arguments.
*   It is called "Variadic function" it is included in 'stdarg.h' header file.
*   You guessed it right! here is a simple examples using variadic func with explanation ;)
*/

#include <stdio.h>
#include <stdarg.h> //for the variadic func sythaxe and code

// variadic function to print the ints passed in arguments
void print_ints(int args, ...) // declaration the "..." tells the function that there is more to come; the variable args to pass the arguments
{
  va_list ap; // will store the extra arguments passed to the func
  //the variable arguments will start after the args parameter
  va_start(ap, args); // va_start says where the variable arguments start
  // C needs to be told the name of the last fixed argument. In the case of our function, that’ll be the args parameter.
  int i;
  for (i = 0; i < args; i++) // to loop through all of the other arguments
    printf("argument: %i\n", va_arg(ap, int)); // args contains a count of how many variables there are.
  va_end(ap); // finished reading all of the arguments
}


// Variadic function to find the largest number
int LargestNumber(int n, ...)
{
  // Declaring pointer to the
  // argument va_list
  va_list ptr;
 
  // Initializing argument to the
  // list pointer
  va_start(ptr, n);
   
  int max = va_arg(ptr, int);
 
  for (int i = 0; i < n-1; i++) {
 
    // Accessing current variable
    // and pointing to next
     int temp = va_arg(ptr, int);
     max = temp > max ? temp : max;
  }
 
  // End of argument list traversal
  va_end(ptr);
 
  return max;
}




int main()
{
  print_ints(3,79,101,32);
  print_ints(5,10,20,30,40,50);

  printf("Largest number among those is : %i \n", LargestNumber(4,10,50,63,78955));

 }
