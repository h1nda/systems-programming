#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char const *argv[])
{
    printf("My process ID (before fork) is %d\n", getpid());

    int pid = fork();

    if (pid == 0) {
        //child
        printf("Result of fork() in child is %d", pid);
        printf("My process ID (c) is %d\n", getpid());
        printf("My parent's process ID is %d\n", getppid());
    } else if (pid > 0) {
        //parent
        printf("Result of fork() in parent is %d", pid);
        printf("My process ID (p) is %d\n", getpid());

        int status;
        wait(&status);

        printf("Child exited with status %d", WEXITSTATUS(status));
    } else {
        perror("error forking");
    }
    return 0;
}
