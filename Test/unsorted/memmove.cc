#include <iostream>
#include <string.h>
using namespace std;
int main()
{
    char s[] = "1234567890";
    char *src = s + 4;
    char *dst = s;
    memcpy(dst,src,7);   
    //memmove(dst,src,7);

    cout<<"dst="<<dst<<endl;

    return 0;
}
