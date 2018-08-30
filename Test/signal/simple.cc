#include <iostream>
#include <signal.h>
#include <unistd.h>

using namespace std;

void signalHandler(int sig)
{
  cout << "Interrupt signal (" << sig << ") received" << endl;

  exit(sig);
}

int main()
{
  int i = 0;
  signal(SIGINT,signalHandler);
  while(++i)
  {
    cout << "Going to sleep..." << endl;
    if(10 == i)
    {
      raise(SIGINT);
    }
    sleep(1);
  }

  return 0;
}
