#include <iostream>
using namespace std;
int main()
{
  int a = 0x1234;
  char c = *(reinterpret_cast<char*>(&a));
  if (c == 0x34)
    cout << "little" << endl;
  else
    cout << "big" << endl;

  return 0;
}
