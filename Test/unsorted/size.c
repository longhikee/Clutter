#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main()
{
  char* p = malloc(1024*1024*1024);
  memset(p,'c' ,1024*1024*1024);
  p[1024*1024*1024 - 1] = '\0';

  printf("%lu\n",strlen(p));

  sleep(100);

  return 0;
/*
  1024			1KB
  1024*1024		1MB
  1024*1024*1024	1GB

*/
}
