// This manipulation was for exploring how "vDSO" is used with ready syscalls like in this example is date.
// VDSO is a shared library mapped into the address space of every user-spce process (in the place of vsyscall)
// You can look for the vdso with:
//	 ldd /bin/uname
#include <sys/time.h>
#include <stdio.h>
#include <time.h>

int main()
{
  struct timeval tv;
  time_t t;
  struct tm *info;
  char buffer [64];

  //Ready to use syscall directly
  gettimeofday(&tv,NULL);
  t = tv.tv_sec;
  info = localtime(&t);

  printf("%s",asctime(info));
  strftime (buffer,sizeof buffer,"Today is %A,%B %d.\n",info);
  printf("%s",buffer);
  strftime (buffer, sizeof buffer,"The time is %I:%M %p.\n",info);
  printf("%s",buffer);

  return 0;
}
