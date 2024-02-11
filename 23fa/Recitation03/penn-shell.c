#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include "inspect.h"
#include "proc_and_pipe.h"
#include "segfault.h"
#include "signals.h"


int main(int argc, char* argv[]) {
  printf("===== PART 0 =====\n");
  fprintf(stderr, "Welcome to \"debugging with %s\"!\n", argv[1]);
  // reading from redirected input file is left as an exercise to the viewer
  exit(EXIT_SUCCESS);

  printf("===== PART 1 =====\n");
  inspect_example();
  exit(EXIT_SUCCESS);

  printf("===== PART 2 =====\n");
  segfault_example();
  exit(EXIT_SUCCESS);

  printf("===== PART 3 =====\n");
  signals_example();
  exit(EXIT_SUCCESS);

  printf("===== PART 4 =====\n");
  proc_and_pipe_example();
  exit(EXIT_SUCCESS);
}

