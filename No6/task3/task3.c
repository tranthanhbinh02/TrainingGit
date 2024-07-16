/* Write a C program to block SIGINT, then check if SIGINT is in the pending
signals, and if so, exit the program */


#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

int main(void) {
    sigset_t newmask, oldmask, pendmask;

    sigemptyset(&newmask);
    sigaddset(&newmask, SIGINT); /

    /
    if (sigprocmask(SIG_BLOCK, &newmask, &oldmask) < 0)
        perror("SIG_BLOCK error");

    while (1) {
        
        if (sigpending(&pendmask) < 0)
            perror("sigpending error");

        if (sigismember(&pendmask, SIGINT)) {
            printf("\nSIGINT is pending\n");
            break;
        }
    }

    return 0;
}
