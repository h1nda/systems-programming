#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
// Да се напише програма на C, която игнорира сигнала SIGPIPE. 
// Създава канал, затваря дескриптора му за четене и пише в него. 
// След това пише на стандартния изход. Какъв е резултата?

// Да се напише програма на C, която обработва сигнала SIGPIPE с подходяща функция. 
// Създава канал, затваря дескриптора му за четене и пише в него. 
// След това пише на стандартния изход. Какъв е резултата?
void handler_sigpipe(int signum) {
    write(2, "Error: All file descriptors referring to the read end have been closed.\n", 73);
    _exit(128+signum);
}
int main(int argc, char const *argv[])
{
    struct sigaction sa;
    sa.sa_handler = &handler_sigpipe;
    sa.sa_flags = 0;

    sigaction(SIGPIPE, &sa, NULL);

    int pipefd[2];

    if (pipe(pipefd) == -1) 
        perror();

    close(pipefd[0]);

    write(pipefd[1], "Coming through the pipe!", 25);

    write(1, "Writing to STDOUT!", 19);


    return 0;
}
