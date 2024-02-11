#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void sig_handler(int signo) {
    if (signo == SIGALRM) {
        printf("Received SIGALRM\n");
    }
}

int main(void) {
    if (signal(SIGALRM, sig_handler) == SIG_ERR) {
        printf("Unable to catch SIGALRM\n");
    }

    alarm(5);

    while(1) {
        sleep(1);
    }

    return 0;
}