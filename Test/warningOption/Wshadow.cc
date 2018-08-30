#include <iostream>
using namespace std;
int main()
{
    for(int i = 0; i < 10; i++)
    {
        for(int i = 0; i < 5; i++)
        {
            cout<<"i="<<i<<" ";
        }
        cout<<"out i="<<i<<endl;    
    }
    for(int i = 0; i < 10; i++)
    {
        cout<<"2rd loop i="<<i<<endl;
    }
    return 0;
}
