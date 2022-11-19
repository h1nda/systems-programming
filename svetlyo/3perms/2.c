
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

int main(int argc, char const *argv[])
{
    struct stat buf;
    for (int i = 1; i < argc; i++) {
        stat(argv[i], &buf);

        printf("File permissions are %o\n", buf.st_mode & 0777);

        chmod(argv[i], buf.st_mode & ~S_IXUSR & ~S_IRGRP);
    }
    return 0;
}
