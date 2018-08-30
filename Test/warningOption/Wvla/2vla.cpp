#include <iostream>
#include <string>
using namespace std;
void display(int *p,int num)
{
    for(int i = 0; i < num; i++)
        cout<<p[i]<<endl;
}
int main()
{
    int count = 3;
    int a[count];
/*    for(int i = 0; i < count; i++)
        a[i] = i;
*/    display(a,count);
}

