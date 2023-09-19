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
  /* open(2)
   * int open(const char *pathname, int flags, mode_t mode);
   * 
   * @param pathname the path to file
   * @param flags the mode we open the file with. Some notable ones are O_RDWR, O_RDONLY, O_WRONLY, O_CREAT
   * @param mode user, group, other permissions in octal digit
   * 
   * @return file descriptor of new file on success (>=0), -1 on fail
   */
  int new_stdout = open("new_stdout", O_WRONLY | O_CREAT, 0644);
  dup2(new_stdout, STDOUT_FILENO);
  write(STDOUT_FILENO, "Hello World!!!", sizeof("Hello World!!!"));
  close(new_stdout);
  exit(0);
}
