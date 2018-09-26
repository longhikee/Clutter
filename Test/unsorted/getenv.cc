#include <stdlib.h>
#include <stdio.h>

int main()
{
  char* p = getenv("PATH");

  if(p)
  {
    printf("%s\n", p);
  }
}
