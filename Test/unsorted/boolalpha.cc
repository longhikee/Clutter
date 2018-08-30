#include <iostream>
#include <sstream>
using namespace std;
int main()
{

  bool t = true;
  cout << noboolalpha << true << endl;

  bool i = true;
  cout << boolalpha << i << endl;

  bool value;
  istringstream ss("true");
  ss >> boolalpha >> value;
  cout << value << endl;
  int tmp = value;
  cout << tmp << endl;

  return 0;
}
