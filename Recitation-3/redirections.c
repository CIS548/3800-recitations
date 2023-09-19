#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

// Build the program with: clang -Wall -o redirections redirections.c
// Run with: ./redirections

// This program redirects stdout to a file and writes to stdout
// the string "Hello World!!!".
int main(void)
{
  int new_stdout = open("new_stdout", O_WRONLY | O_CREAT, 0644);
  dup2(new_stdout, STDOUT_FILENO);
  write(STDOUT_FILENO, "Hello World!!!", sizeof("Hello World!!!"));
  close(new_stdout);
  exit(0);
}
