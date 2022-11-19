#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

int main(int argc, char const *argv[])
{
    printf("My process ID is %d\n", getpid());
    printf("My parent's process ID is %d\n", getppid());

    execlp("ps", "ps", 0);
    
    return 0;
}
