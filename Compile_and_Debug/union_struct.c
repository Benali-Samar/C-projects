#include <stdio.h>


struct struct_test{
int x;
int y;
};

union Union_test{
int intval;
float floatval;
};


int main()
{
//struct_test

struct struct_test S1 = {10,20};
printf("Coordinates: (%d,%d)\n", S1.x,S1.y);


//union_test
union Union_test u;

u.intval=42;
printf("Integer value: %d\n",u.intval);// it gives 42

u.floatval=3.14;
printf("Float value: %f\n", u.floatval); // it gives 3.14


printf("Integer value after changing the union vals: %d\n",u.intval); // it gives : 1078523331
// because in unions , all members share the same memory space, when you assign a value to one member and then assign a value to another member, it can lead to unexpected results because the memory is shared.
// so the "1078523331" value is the bytes interpreted of the float"3.14" as an integer.

// Both int and float have the sie of 4 bytes in the memory, but as the memory is shared, those 4 bytes are whether the number 4 or the number 3.14.
// To prevent this from hapening while working with unions, it is better to reassign the value needed befor using the union memeber.




return 0;
}
