#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>

int main(void) {
    char buf[51];
    // buf[0]='s';
    // printf("%s\n", buf);
    ssize_t bytesRead = read(STDIN_FILENO, buf, 50);

    // buf[res] = '\0';   // valgrind

    printf("buf is: %s, strlen: %ld, bytesRead: %ld\n", buf, strlen(buf), bytesRead);

    return 0;
}