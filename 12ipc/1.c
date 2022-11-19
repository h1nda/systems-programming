#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
// Да се напише програма на C, която синхронизира два родствени процеса чрез сигнали.
// Двата процеса пишат текст на стандартния изход в следния ред - единия, другия, отново първия.
// Процеса който пише пръв, изчаква няколко секунди преди да пише.

void handler_sigusr1(int signum)
{
    
}

int main(int argc, char const *argv[])
{
    // Set signal handler for both processes
    struct sigaction sa;
    sa.sa_handler = &handler_sigusr1;
    sa.sa_flags = 0;
    sigaction(SIGUSR1, &sa, NULL);

    int pid = fork();

    if (pid == -1)
        perror();

    if (pid == 0)
    {
        // Child process
        // First printing.
        sleep(1);
        write(STDOUT_FILENO, "Go to sleep!!\n", 15);
        kill(getppid(), SIGUSR1);

        // After the parent can execute their code:
        while (1)
        {
            pause();
            write(STDOUT_FILENO, "Go to sleep!!\n", 15);
            kill(getppid(), SIGUSR1);
        }
    }
    else
    {
        // Wait for signal then send signal
        while (1)
        {
            pause();
            write(STDOUT_FILENO, "No way!!\n", 10);
            kill(pid, SIGUSR1);
        }
    }

    return 0;
}