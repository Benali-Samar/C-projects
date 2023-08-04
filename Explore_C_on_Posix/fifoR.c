// named pipe to read from file

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

int main (void) {
  int fd;
  FILE *fp;
  char *filename = "/tmp/fifo.txt";
  char charac [100];

  fd = open (filename, O_RDONLY);
  fp = fdopen (fd, "r");
  fscanf (fp, "%s", charac);
  puts (charac);
  unlink (filename);
  return 0;
}
