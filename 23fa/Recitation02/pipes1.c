#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <assert.h>
#include <sys/wait.h>

// Build the program with: clang -Wall -o pipes1 pipes1.c
// Run with: ./pipes1

// The program does the following: ls -la | more
int main(int argc, const char *argv[])
{
  int fd[2];
  pipe(fd);

  // Create one child process for more
  int pid = fork();
  if (pid == 0)
  {
    int ret = dup2(fd[0], 0); // read from standard in
    if (ret < 0)
      perror("dup2");
    char *argv[10];
    argv[0] = "more";
    argv[1] = NULL;

    close(fd[0]);
    close(fd[1]); // close write end

    execvp("more", argv);
    assert(0);
  }
  // Create another child process for ls
  int pid2 = fork();
  if (pid2 == 0)
  {
    int ret = dup2(fd[1], 1); // write to standard out
    if (ret < 0)
      perror("dup2");
    char *argv[10];
    argv[0] = "ls";
    argv[1] = "-l";
    argv[2] = NULL;
    close(fd[0]);
    close(fd[1]);
    execvp("ls", argv);
  }

  // close parent's pipes
  close(fd[0]);
  close(fd[1]);

  // wait for the more process to finish
  int status;
  waitpid(pid, &status, 0);
  waitpid(pid2, &status, 0);

  printf("Done!\n");
  return 0;
}
