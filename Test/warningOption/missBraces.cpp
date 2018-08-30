#include <iostream>

struct B{
    const char *a;
    char b;
};
struct A{
    int a;
    struct B b;
};
int main()
{
    struct A a[2] = {
    {1,{"first",1}},
    {2,{"second",2}},
    };
    struct A b;
    std::cout<<b.a<<" "<<b.b.b<<std::endl;
}
