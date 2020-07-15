#include <iostream>
using namespace std;

typedef void (*FUNC)(int i);
void (*func)(int i);
void function(int i)
{
    cout << "function i ="  << i << endl;
}

int main()
{
    FUNC f1 = FUNC(&function);
    f1(1);


    FUNC f2 = FUNC(function);
    f2(2);

    FUNC f3 = function;
    (*f3)(3);

    FUNC f4 = &function;
    (*f4)(4);
    f4(5);

    func = function;
    func(6);

    return 0;
}
