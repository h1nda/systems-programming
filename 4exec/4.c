#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
int main(int argc, char const *argv[])
{
    int pid1 = fork();

    if (pid1 == 0) {
        //child - executes one command
        execlp(argv[2],argv[2],0);

    } else {
        //parent
        int pid2 = fork();

        if (pid2 == 0) {
            //anoter child of parent - executes one command
            execlp(argv[1],argv[1],0);

        } else {
            //actual parnet
            int status;
            int cpid = waitpid(-1, &status, 0);
            printf("The fastest child (pid = %d) exited with status %d\n",cpid, WEXITSTATUS(status));

            cpid = waitpid(-1, &status, 0);
            printf("The slower child (pid = %d) exited with status %d\n",cpid, WEXITSTATUS(status));

        }
    }
    return 0;
}
