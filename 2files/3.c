#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
// Да се напише програма на C, която получава списък с имена 
// на файлове в командния ред 
// и извежда по подходящ начин stat информацията за всеки от тях.
void printinfo(struct stat *stst) {
    printf("Size of file is %d, its' permissions is %o,  and last modification was on %d\n", stst->st_size, stst->st_mode & 0777, stst->st_atime);
    if (S_ISREG(stst->st_mode))
        printf("File is a regular file.\n");
}
int main(int argc, char const *argv[])
{
    struct stat buf;
    for (int i = 1; i < argc; i++) {
        stat(argv[i], &buf);
        printinfo(&buf);
    }
    return 0;
}
