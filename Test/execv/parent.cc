#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
using namespace std;

int main()
{
  pid_t fd = fork();
  if (fd < 0)
  {
    cout << "error" << endl;
    return -1;
  }
  else if (0 == fd)
  {
    cout << "child process sleep" << endl;
    execv("sleep", NULL);
    cout << "child exit" << endl;  //child process is replaced by sleep, this line won't print
  }
  else
  {
    cout << "child pid: " << fd << endl;
    cout << "parent pid: " << getpid() << endl;
sleep(10);
    pid_t pid = -1;
    int status;
    if ((pid = waitpid(-1, NULL, WNOHANG)) > 0);  //WNOHANG waitpid will not hang just return 0
      cout << "waitpid WNOHANG return " << pid << " line: " <<  __LINE__ << endl;
    if ((pid = waitpid(-1, &status, NULL)) > 0)  //child pid won't be zombie when it exit
    {
      cout << "pid: " << pid << " return." << "line:" << __LINE__ << endl;
      if (WIFEXITED(status) || WEXITSTATUS(status))
        cout << "process with pid" << pid << "exit with code " << WEXITSTATUS(status) << endl;
      if (WIFSIGNALED(status))
        cout << "process with pid" << pid << "terminate by signal " << WTERMSIG(status) << endl;
    }

    cout << "parent begin to sleep 10s" << endl;
    sleep(10);
    cout << "parent exit" << endl;
  }

  cout << "pid: " << getpid() << " main done" << endl;
  return 0;
}
