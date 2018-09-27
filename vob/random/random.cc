#include <iostream>
#include <stdlib.h> //linux is random and rand
#include <time.h>
using namespace std;

int main()
{
  time_t t;
  t = time(NULL);
//  cout << t << endl;

  srand(t);
  cout << rand() << endl;

}
