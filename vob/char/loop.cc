#include <iostream>
#include <stdlib.h>
using namespace std;

#define LOOP_NUM 100

int main(int argc, char** argv)
{
  if (argc < 2)
  {
    cout << "Usage:" << endl;
    cout << "parameter: ";
    cout << "loop exe + loop number" << endl;
    return -1;
  }

  int loop = 0;
  if (argc < 3)
  {
    loop = LOOP_NUM;
  }
  else
  {
    loop = atoi(argv[2]);
  }

  do{
  system(argv[1]);
  loop--;
  }while(loop>0);

  return 0;
}
