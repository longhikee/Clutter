#include <iostream>
#include <signal.h>

using namespace std;

void signalHandler(int sig)
{
  cout << "Interrupt signal (" << sig << ") received" << endl;

  //to do 
  //switch(sig)
  
}

int main()
{
  int siglist[] = { SIGALRM, SIGHUP, SIGINT, SIGQUIT, SIGILL, SIGTRAP, SIGIOT,
		SIGEMT, SIGFPE, SIGBUS, SIGSEGV, SIGSYS, SIGPIPE,
		SIGTERM, SIGUSR1, SIGUSR2, SIGCLD, SIGCHLD, SIGPWR,
		SIGWINCH, SIGURG, SIGPOLL, SIGIO, SIGTSTP, SIGCONT,
		SIGTTIN, SIGTTOU, SIGVTALRM, SIGPROF, 0 };
  struct sigaction sig;

  sig.sa_flags = 0;
  sig.sa_handler = signalHandler;
  sigfillset(&sig.sa_mask);

  for (i=0; siglist[i] != 0; i++)
  {
    sigaction(siglist[i], &sig, 0);
  }


  return 0;
}
