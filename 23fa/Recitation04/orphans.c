#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

int main() {
  int status;
  pid_t pid1 = fork();
  if (pid1 == 0) {
    char* args[] = {"sleep", "1000", NULL};
    if (execvp(args[0], args) < 0) perror("exec");
  }

  pid_t pid2 = fork();
  if (pid2 == 0) {
    char* args[] = {"echo", "hi", NULL};
    if (execvp(args[0], args) < 0) perror("exec");
  }

  wait(&status);
  fprintf(stderr, "waited!");
}