#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

int main() {
  int counter = 0;
  while (counter < 2) {
    int status;
    if (counter) {
      pid_t pid1 = fork();
      if (pid1 == 0) {
        char* args[] = {"sleep", "100", NULL};
        if (execvp(args[0], args) < 0) perror("exec");
      }
    } else {
      pid_t pid = fork();
      if (pid == 0) {
        char* args[] = {"sleep", "3", NULL};
        if (execvp(args[0], args) < 0) perror("exec");
      }
    }
    waitpid(-1, &status, WNOHANG);
    counter++;
  }
  sleep(5);
}