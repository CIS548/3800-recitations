#include <stdio.h>
#include "inspect.h"

int fibonacci(int n) {
  if (n == 0 || n == 1) {
    return n;
  }
  return fibonacci(n-1) + fibonacci (n-2);
}

void read_msg(int id, struct Message* msg) {
  if (msg == NULL) {
    fprintf(stderr, "Invalid message\n");
    return;
  }

  // idk who would code this
  // but this is good for a demo
  int err = 0;
  for (int i = id - 1; i <= id + 1; i++) {
    if (msg->id != i) {
      err++;
    }
  }

  if (err == 3) {
    fprintf(stderr, "you're an idiot sandwich\n");
  } else {
    fprintf(stderr, "where's the %s\n", msg->text);
  }
}

void inspect_example() {
  int n = fibonacci(6);
  fprintf(stderr, "Fibonacci: %d\n", n);

  struct Message msg = {
    5,
    "chick fil a sauce"
  };
  fprintf(stderr, "Inspecting message\n");
  read_msg(3, &msg);
}
