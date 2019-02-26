#include <iostream>

#include <unistd.h>
#include <signal.h>
#include <pthread.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>

using namespace std;
void signal_handler(int sig)
{
  switch (sig)
  {
    case SIGABRT :
    case SIGSEGV :
    case SIGBUS :
    {
      char cmd[512];
      pid_t pid = getpid();
      sprintf(cmd, "pstack %d > %d.pstack", pid, pid);
      system(cmd);

      signal(sig, SIG_DFL); //restore defualt signal handler
      raise(sig);
    }
    break;
    default:
    break;
  }

}

void signal_handler_init()
{
  sigset_t sigSet, sigSetOld;
  sigemptyset(&sigSet);
  sigemptyset(&sigSetOld);
  sigaddset(&sigSet, SIGABRT);
  sigaddset(&sigSet, SIGSEGV);
  sigaddset(&sigSet, SIGBUS);

  struct sigaction sa;
  sigset_t mask;
  sigfillset(&mask);
  int flags = SA_SIGINFO;
  sa.sa_mask = mask;
  sa.sa_flags = flags;
  sa.sa_handler = signal_handler;
  
  pthread_sigmask(SIG_SETMASK, &mask, &sigSetOld); // block all signals
  for (int sig_no = 0; sig_no < 31; sig_no++)
  {
    if (sigismember(&sigSet, sig_no))
    {
      cout << "add signal " << sig_no << " to list" << endl;
      sigaction(sig_no, &sa, NULL);
    }
  }
}


void* start_thread1(void* arg)
{
  cout << "start_thread1 enter" << endl;
  // double free signal 6 test
  {
  int* i = new int;
  delete i;
  delete i;
  }
  sleep(10);
  cout << "start_thread1 exit" << endl;
}

void* start_thread2(void* arg)
{
  sleep(1);
  cout << "start_thread2 enter" << endl;
  sleep(100);
  cout << "start_thread2 exit" << endl;
}

int main()
{
  pid_t pid = fork();
  if (pid < 0)
    return -1;
  else if (pid == 0)
  {
    signal_handler_init();

    pthread_t thread_id;
    pthread_create(&thread_id, NULL, start_thread1, NULL);
    pthread_create(&thread_id, NULL, start_thread2, NULL);
    //sleep(1000);
    cout << getpid() << " main thread quit" << endl;
    pthread_exit(NULL); //just thread quit
    return 0; //main will call exit to quit whole process
  }
  else
  {
    int status = 0;
    if(waitpid(pid, &status, 0) > 0) {
    if (WIFEXITED(status) || WEXITSTATUS(status)) {
      cout << "child process " << pid << " exit with code " << WEXITSTATUS(status) << endl;
      }
    if (WIFSIGNALED(status)) {
      cout << "child process " << pid << " exit by signal " << WTERMSIG(status) << endl;
      }
    }
    cout << "father process waitpid done" << endl;
    sleep(1000);
  }

  cout << "exit" << endl;
  return 0;
}
