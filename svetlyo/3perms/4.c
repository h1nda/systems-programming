#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <utime.h>

int main(int argc, char const *argv[]) {
    if (link(argv[1], argv[2]) == -1)
        perror("err");
    
    unlink(argv[1]);
    return 0;
}