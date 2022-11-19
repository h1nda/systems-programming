#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

int main(int argc, char const *argv[])
{
    int pid = fork();

    if (pid == 0) {
        //child
        char command[256] = "./";
        strcat(command,argv[1]);
        if (execlp(command, command, 0) == -1) {
            return -1;
        }
    } else if (pid > 0) {
        int status;
        wait(&status);
        printf("Child ended with status %d", WEXITSTATUS(status));
    }
    return 0;
}
