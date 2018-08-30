#include <iostream>
using namespace std;
void func(short& i);
void func2(int*& j);
void func3(int*& j);
int main()
{
    int i = 0;
    cout<<"before call, main i="<<i<<endl;
    func(reinterpret_cast<short&>(i));
    cout<<"after call, main i="<<i<<endl;

    int *j = &i;
    func2(j);
    cout << *j << endl;

    func3(j);
    cout << *j << endl;

    return 0;
}
void func(short& i)
{
    i = 2;
    cout<<"func i="<<i<<endl;

}
void func2(int* &j)
{
    *j = 3;
}
void func3(int* &j)
{
    int* p = new int(10);
    j = p;
}
