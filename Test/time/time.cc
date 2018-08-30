#include <iostream>
#include <time.h>

using namespace std;

int main()
{

  time_t t;
  t = time(NULL);
  cout << t << endl;

  struct tm* t_ptr;
  t_ptr = localtime(&t);

  cout << t_ptr->tm_hour << ":" << t_ptr->tm_min << ":" << t_ptr->tm_sec << endl;

  t_ptr = gmtime(&t);
  cout << asctime(t_ptr) << endl;
  cout << ctime(&t) << endl;

  return 0;
}
