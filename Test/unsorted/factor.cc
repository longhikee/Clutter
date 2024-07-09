#include <iostream>
#include <stdlib.h>
using namespace std;

int main(int argc, char** argv)
{
  if (argc < 2)
  {
    return -1;
  }

  long long num = atoll(argv[1]);
  cout << num << ": ";
  for (int divisor = 2; num > 1; divisor++) {
    for (; num % divisor == 0; num /= divisor) {
      cout << divisor << " ";
    }
  }
  cout << endl;

  return 0;
}
