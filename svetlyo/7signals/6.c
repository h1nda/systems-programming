#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include <stdio.h>
#include <sys/types.h>  /* include this before any other sys headers */
#include <sys/wait.h> 

// Да се напише програма на C, която поражда процес. 
// Сина обработва сигнала SIGTERM, като извежда подходящо съобщение. 
// Бащата изпраща 2 пъти през 1 секунда сигнала SIGTERM на сина си. 
// Какъв е резултата?

void handler_sigterm(int signum) {
    write(1, "\nI've received a SIGTERM signal\n", 33);
    _exit(signum+128);
}

int main(int argc, char const *argv[])
{
    int pid = fork();

    if (pid == -1)
        return -1;

    if (pid == 0) {
        // Child process
        struct sigaction sa;
        sa.sa_handler = &handler_sigterm;
        sa.sa_flags = 0;
        sigaction(SIGTERM, &sa, NULL);

        while (1) {
            write(1,"Loop",5);
        };

    } else {
        // Parent process
        sleep(1);
        kill(pid,SIGTERM);
        sleep(1);
        kill(pid,SIGTERM);

        int cstatus;

        wait(&cstatus);

        printf("Exit of child was: %d\n", WEXITSTATUS(cstatus));

    }
    return 0;
}
