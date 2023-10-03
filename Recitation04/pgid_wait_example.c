#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

int main() {
  pid_t cpid = fork();
  if (cpid < 0) perror("fork");
  if (cpid == 0) {
    fprintf(stderr, "  pgid of Child is %d\n", (int) getpgrp());
    fprintf(stderr, "  pid of Child is %d\n", (int) getpid());
    fprintf(stderr, "  ppid of Child is %d\n\n", (int) getppid());
    
    pid_t gcpid = fork();
    if (gcpid < 0) perror("fork gc");
    if (gcpid == 0) {
      fprintf(stderr, "    pgid of Grand-Child is %d\n", (int) getpgrp());
      fprintf(stderr, "    pid of Grand-Child is %d\n", (int) getpid());
      fprintf(stderr, "    ppid of Grand-Child is %d\n\n", (int) getppid());
      char* args[] = {"sleep", "1000", NULL}; //change to 1 and waitpid(-1)
      if (execvp(args[0], args) < 0) perror("exec");
    }

    setpgrp(); //set process group, equivalent to setpgid(0,0)
    pid_t pgid = getpid();
    pid_t gcpid2 = fork();
    if (gcpid2 < 0) perror("fork gc");
    if (gcpid2 == 0) {
      fprintf(stderr, "    pgid of Grand-Child2 is %d\n", (int) getpgrp());
      fprintf(stderr, "    pid of Grand-Child2 is %d\n", (int) getpid());
      fprintf(stderr, "    ppid of Grand-Child2 is %d\n\n", (int) getppid());
      char* args[] = {"sleep", "5", NULL};
      if (execvp(args[0], args) < 0) perror("exec");
    }

    int cstatus;
    waitpid(-pgid, &cstatus, 0);
  } else {
    fprintf(stderr, "pgid of Parent is %d\n", (int) getpgrp());
    fprintf(stderr, "pid of Parent is %d\n", (int) getpid());
    fprintf(stderr, "ppid of Parent is %d\n\n", (int) getppid());
    int status;
    wait(&status);
  }
}