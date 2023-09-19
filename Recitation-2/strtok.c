#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>

int main(void) {
    char buf[27] = "Welcome to CIS recitation!\0";
    printf("buf is: %s\n", buf);
    
    char * tok;
    tok = strtok(buf, " ");
    while (tok != NULL) {
        printf("    token: %s\n", tok);
        tok = strtok(NULL, " ");
    }

    printf("buf is: %s, %ld\n", buf, strlen(buf));
    return 0;
}