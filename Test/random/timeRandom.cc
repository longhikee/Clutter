#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace std;

int main()
{
  time_t t;
  t = time(NULL);

  srand(t);

  t ^= rand();

  srand(t);

  cout << rand() << endl;

  return 0;
}
