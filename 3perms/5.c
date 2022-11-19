#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <utime.h>

int main(int argc, char const *argv[]) {
    symlink(argv[1], argv[2]);

    int fd = open(argv[2], O_RDONLY);

    char buf[1];

    while (read(fd,buf,1)) {
        write(1,buf,1);
    }
    return 0;
}