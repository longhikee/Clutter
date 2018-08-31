#include <io.h>
#include <direct.h>
#include <string>
#include <iostream>

using namespace std;

int main()
{
  int ret;
  //success ret eq 0
  ret = ::_access("testfolder", 0);
  cout << ret << endl;

  ret = ::_mkdir("testfolder");
  cout << ret << endl;

  ret = ::_rmdir("testfolder");
  cout << ret << endl;

  return 0;
}
