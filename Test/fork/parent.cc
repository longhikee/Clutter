#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
using namespace std;

int main()
{
  cout << "parent in ..." << endl;
/*
  system("sleep");

  cout << "begin to sleep 30s" << endl;
  sleep(30);
*/
  pid_t fd = fork();
  if (fd < 0)
  {
    cout << "error" << endl;
    return -1;
  }
  else if (0 == fd)
  {
    cout << "child process sleep" << endl;
    system("sleep&");
    system("sleep");
    system("sleep&");
//    getchar();
    cout << "child exit" << endl;
  }
  else
  {
    cout << "child pid: " << fd << endl;
    cout << "parent pid: " << getpid() << endl;
    cout << "parent begin to sleep" << endl;
    sleep(30);
    cout << "parent exit" << endl;
  }

  cout << "pid : " << getpid() << " main done" << endl;

  return 0;
}
