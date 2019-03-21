#include <signal.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#include <sys/stat.h>
#include <fcntl.h>

int main()
{
  pid_t pid = getpid();

  char pidbuf[10];
  sprintf(pidbuf, "%d1", pid);

  int fd = open("tmp.txt", O_WRONLY | O_CREAT, 0666);
  if (fd != 1) {
    dup2(fd, 1);
    close(fd);
  }
  execl("/usr/bin/pstack", "pstack", pidbuf, 0);

  return 0;
}
