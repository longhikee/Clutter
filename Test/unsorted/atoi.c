#include <stdio.h>
#include <stdlib.h>
int main()
{
    char *s="12s345";
    int i = atoi(s);
    printf("%i\n",i);

    char* a="22345699999";
    char* endptr;
    long long j = strtoll(a,&endptr,10);
    printf("%i\n",j);
}
