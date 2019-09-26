#include <iostream>
#include <bitset>
#include <string>
using namespace std;

int main()
{
  char int8 = 3;
  cout << bitset<sizeof(int) * 8>(int8) << endl;
  char s = int8 << 3;
  cout << bitset<sizeof(int) * 8>(s) <<  endl;

  string str;
  s = 97;
  str.assign(1, s);
  cout << str << endl;

  return 0;
}
