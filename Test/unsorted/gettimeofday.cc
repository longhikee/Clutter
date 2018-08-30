#include <iostream>
#include <sys/time.h>
using namespace std;
int main()
{
    timeval tv;
    //timezone* tz = NULL;
    gettimeofday(&tv,NULL);

    cout << tv.tv_sec << endl;
    cout << tv.tv_usec << endl;

    return 0;
}
