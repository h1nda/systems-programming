#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

int main(int argc, char const *argv[])
{
    struct stat buf;
    int fd = open("newfile.txt", O_CREAT|O_TRUNC|O_WRONLY, 0777);
    fstat(fd, &buf);
    printf("File permissions are %o\n", buf.st_mode & 0777);

    mode_t oldmask = umask(077);
    printf("Old mask was %o\n",oldmask);

    int fd1 = open("newfile2.txt", O_CREAT|O_TRUNC|O_WRONLY, 0777);
    fstat(fd1, &buf);
    printf("File permissions are %o\n", buf.st_mode & 0777);

    return 0;
}