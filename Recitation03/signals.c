#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

void handle_sigint(int sig) {
  fprintf(stderr, "Caught SIGINT %d\n", sig);
  // reset signal handler to default
  // what is SIGINT's behavior by default?
  signal(SIGINT, SIG_DFL);
}

void signals_example() {
  signal(SIGINT, handle_sigint);
  unsigned long counter = 0;
  while(1) {
    fprintf(stderr, "Counting: %lu\n", counter++);
    sleep(1);
  }
}

