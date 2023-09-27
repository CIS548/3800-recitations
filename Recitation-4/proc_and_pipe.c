#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include "proc_and_pipe.h"

void handle_child(bool use_in_txt, bool use_out_txt) {
  // note that functions being used here are mostly
  // **illegal** in project 0, 1, 2
  if (use_in_txt) {
    FILE* fp = fopen("in.txt", "r");
    dup2(fileno(fp), STDIN_FILENO);
    fclose(fp);
  }
  if (use_out_txt) {
    FILE* fp = fopen("out.txt", "w");
    dup2(fileno(fp), STDOUT_FILENO);
    fclose(fp);
  }

  fprintf(stderr, "(child) i'm going to cat < in.txt\n");
  system("/bin/cat");
  exit(EXIT_SUCCESS);
}

void handle_parent(pid_t pid) {
  fprintf(stderr, "(parent) waiting for child: %d\n", pid);
  wait(NULL);
  fprintf(stderr, "(parent) done waiting\n");
}

void proc_and_pipe_example() {
  bool use_out_txt = false;
  bool use_in_txt = true;

  pid_t pid = fork();
  if (pid < 0) {
    perror("fork");
  } else if (pid == 0) {
    // handle_child(use_in_txt, use_out_txt); SOLUTION
    handle_child(use_out_txt, use_in_txt);
  } else {
    handle_parent(pid);
  }
}

