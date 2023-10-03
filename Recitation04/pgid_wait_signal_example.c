#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

int main() {
  int status;
  pid_t pid1 = fork();
  setpgid(pid1, pid1);
  if (pid1 == 0) {
    char* args[] = {"sleep", "1000", NULL};
    if (execvp(args[0], args) < 0) perror("exec");
  }

  pid_t pid2 = fork();
  setpgid(pid2, pid1);
  if (pid2 == 0) {
    char* args[] = {"echo", "hi", NULL};
    if (execvp(args[0], args) < 0) perror("exec");
  }

  pid_t pid3 = fork();
  setpgid(pid3, pid1);
  if (pid3 == 0) {
    sleep(5);
    fprintf(stderr, "sending stop!\n");
    kill(0, SIGSTOP);
  }

  do {
    waitpid(-pid1, &status, WUNTRACED);
    fprintf(stderr, "waiting....!\n");
  } while (!WIFSTOPPED(status));
  fprintf(stderr, "waiting done!\n");
}