#include <iostream>
using namespace std;
void func(int* p)
{
    cout << "p = " << p <<endl;
    int* number = new int(10);
    p = number;
    cout << "p after = " << p <<endl;
    cout << "*p= " << *p << endl;
}

int main()
{
    int* pointer = new int(1);
//    cout << pointer <<endl;
//    func(pointer);
//    cout << "pointer addr after " << pointer << endl;
//    cout << *pointer <<endl;

    int a = 10;
    cout << "a addr= " << &a <<endl;
    func(&a);
    cout << "a addr after: "  << &a <<endl;
    cout << "a= " << a << endl;
    return 0;
}
