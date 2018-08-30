#include <iostream>
using namespace std;
struct A{
    int a;
    char b;
};
int main()
{
    struct A a;	//no warning
    struct A Array[2];
    int i; 	//warning uninitialized
    int array[4];
    cout<<a.a;
    cout<<endl<<i<<endl;
    cout<<array[0]<<endl;
    cout<<Array[0].b<<endl;
}
