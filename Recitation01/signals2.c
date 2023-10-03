#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void sig_handler(int signo) {
    if (signo == SIGINT) {
        printf("Received SIGINT\n");
    }
    if (signo == SIGKILL) {
        printf("Received SIGKILL\n");
    }
    if (signo == SIGSTOP) {
        printf("Received SIGSTOP\n");
    }
}

int main(void) {
    if (signal(SIGINT, sig_handler) == SIG_ERR) {
        printf("Unable to catch SIGINT\n");
    }

    if (signal(SIGKILL, sig_handler) == SIG_ERR) {
        printf("Unable to catch SIGKILL\n");
    }

    if (signal(SIGSTOP, sig_handler) == SIG_ERR) {
        printf("Unable to catch SIGSTOP\n");
    }

    while(1) {
        sleep(1);
    }

    return 0;
}