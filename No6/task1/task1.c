/* Write a C program to block the Ctrl + C signal (SIGINT) from the user*/

#include<stdio.h>
#include<signal.h>

void main()
{
    sigset_t sig_mask;
    sigemptyset(&sig_mask);

    sigaddset(&sig_mask, SIGINT);
    sigprocmask(SIG_BLOCK, &sig_mask,NULL);
    while(1);
}
