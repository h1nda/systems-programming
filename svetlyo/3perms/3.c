#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <utime.h>

int main(int argc, char const *argv[])
{
    struct stat sbuf;
    stat(argv[1], &sbuf);
    printf("Previous last access time %d, previous last modification time %d\n", sbuf.st_atime, sbuf.st_mtime);
    
    struct utimbuf tbuf;
    tbuf.actime = sbuf.st_atime - 60*60;
    tbuf.modtime = sbuf.st_mtime + 1*60;

    utime(argv[1], &tbuf);
    printf("New last access time %d, supposed last modification time %d\n", tbuf.actime, tbuf.modtime);

    struct stat sbuf1;
    stat(argv[1], &sbuf1);
    printf("New last access time %d, new last modification time %d\n", sbuf1.st_atime, sbuf1.st_mtime);


    return 0;
}
