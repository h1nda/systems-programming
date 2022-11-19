#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
// Да се напише програма на C, която поражда процес.
// Без да ползва функцията wait(), изчаква завършването му и извежда подходящо съобщение.

void signal_sigusr1(int signum) {
    return;
}

int main(int argc, char const *argv[])
{
    int pid = fork();

    if (pid == -1) 
        perror();
    
    if (pid == 0) {
        //Child process
        sleep(5);
        write(1, "I'm done napping :).\n", 22);
        kill(getppid(), SIGUSR1);

    } else {
        //Parent process
        struct sigaction sa;
        sa.sa_handler = &signal_sigusr1;
        sa.sa_flags = 0;
        sigaction(SIGUSR1, &sa, NULL);

        pause();
        write(1, "Hello?\n", 8);
    }
    return 0;
}
