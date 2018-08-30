#include <iostream>

int old_fn () __attribute__ ((deprecated));
int (*fn_ptr)() = old_fn;
int main()
{

}
