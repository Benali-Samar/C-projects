#include "encrypt.h"

void encrypt(char *msg)
{
  char c;
  while(*msg)
  {
    *msg = *msg ^ 31;
    msg++;
  }
}
