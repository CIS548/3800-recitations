#include<unistd.h>
#include<sys/wait.h>
#include<sys/types.h>
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>

int main (int argc, const char * argv[]) {
  int pipe_fds[2];

  if (pipe(pipe_fds) < 0) {
    perror("pipe error");
    exit(EXIT_FAILURE);
  }

  // Create a child process for ls
  int pid0 = fork();
  if (pid0 == 0) {
    // close the fds we don't need
    close(pipe_fds[0]);

    // redirect standard out to write to the first pipe
    int ret = dup2(pipe_fds[1], STDOUT_FILENO);
    if (ret < 0) {
      perror("dup2");
      exit(EXIT_FAILURE);
    }

    // close original fd that writes to pipe now that we are done with it
    close(pipe_fds[1]);
    
    char *argv[] = {"ls", "-l", NULL};

    execvp(argv[0], argv);

    exit(EXIT_FAILURE);
  }

  // close write end of the first pipe, only the first child neede it
  close(pipe_fds[1]);


  // create pipe output for second child
  int pipe2_fds[2];
  if (pipe(pipe2_fds) < 0) {
    perror("pipe error");
    exit(EXIT_FAILURE);
  }

  // Create one child process for `cat`
  int pid1 = fork();
  if (pid1 == 0) {
    // close the ends of the pipes we don't need
    close(pipe2_fds[0]); // read end of the second pipe

    // redirect stdin to instead read from the first pipe
    int ret = dup2(pipe_fds[0], STDIN_FILENO);
    if (ret < 0) {
      perror("dup2");
      exit(EXIT_FAILURE);
    }
    // close original fd that reads from the first pipe now that we are done with it
    close(pipe_fds[0]);

    // redirect stdout to instead print to the second pipe
    ret = dup2(pipe2_fds[1],STDOUT_FILENO);
    if (ret < 0) {
      perror("dup2");
      exit(EXIT_FAILURE);
    }
    // close original fd that writes to the second pipe now that we are done with it
    close(pipe2_fds[1]);
    
    char *argv[] = {"cat", NULL};
    execvp(argv[0], argv);

    exit(EXIT_FAILURE);
  }

  // no more processes need to write to second pipe or read from first pipe
  close(pipe_fds[0]);
  close(pipe2_fds[1]);

  // Create one child process for `wc`
  int pid2 = fork();
  if (pid2 == 0) {
    // redirect stdin to instead read from the second pipe
    int ret = dup2(pipe2_fds[0],STDIN_FILENO); 
    if (ret < 0) {
      perror("dup2");
      exit(EXIT_FAILURE);
    }
    // close original fd that reads from the second pipe now that we are done with it
    close(pipe2_fds[0]);
    
    char *argv[] = {"wc", NULL};
    execvp(argv[0], argv);

    exit(EXIT_FAILURE);
  } 

  printf("%d %d %d\n", pid0, pid1, pid2);

  // close the last acecss parent has to the pipes
  close(pipe2_fds[0]);

  // wait for the three processes to finish
  int status;
  waitpid(pid0, &status, 0);
  waitpid(pid1, &status, 0);
  waitpid(pid2, &status, 0);
  printf("Done!\n");
  return 0;
}