#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>

int main() {
    const char *signal_names[] = {
        "SIGHUP", "SIGINT", "SIGQUIT", "SIGILL", "SIGTRAP", "SIGABRT", "SIGBUS", "SIGFPE",
        "SIGKILL", "SIGUSR1", "SIGSEGV", "SIGUSR2", "SIGPIPE", "SIGALRM", "SIGTERM", "SIGSTKFLT",
        "SIGCHLD", "SIGCONT", "SIGSTOP", "SIGTSTP", "SIGTTIN", "SIGTTOU", "SIGURG", "SIGXCPU",
        "SIGXFSZ", "SIGVTALRM", "SIGPROF", "SIGWINCH", "SIGIO", "SIGPWR", "SIGSYS", "SIGRTMIN",
        "SIGRTMIN+1", "SIGRTMIN+2", "SIGRTMIN+3", "SIGRTMIN+4", "SIGRTMIN+5", "SIGRTMIN+6", "SIGRTMIN+7", "SIGRTMIN+8",
        "SIGRTMIN+9", "SIGRTMIN+10", "SIGRTMIN+11", "SIGRTMIN+12", "SIGRTMIN+13", "SIGRTMIN+14", "SIGRTMIN+15", "SIGRTMAX-14",
        "SIGRTMAX-13", "SIGRTMAX-12", "SIGRTMAX-11", "SIGRTMAX-10", "SIGRTMAX-9", "SIGRTMAX-8", "SIGRTMAX-7", "SIGRTMAX-6",
        "SIGRTMAX-5", "SIGRTMAX-4", "SIGRTMAX-3", "SIGRTMAX-2", "SIGRTMAX-1", "SIGRTMAX"
    };
    sigset_t sig_mask;
    sigemptyset(&sig_mask);
    int result;

    sigaddset(&sig_mask, SIGINT);
    sigprocmask(SIG_BLOCK, &sig_mask, NULL);

    sigset_t sig_mask_current;
    sigprocmask(SIG_BLOCK, NULL, &sig_mask_current);

    for (int i = 0; i < 62; i++)
    {
        if (sigismember(&sig_mask_current, i + 1))
        {
            printf("%s\n", signal_names[i]);
        }
    }

 
    return 0;
}
