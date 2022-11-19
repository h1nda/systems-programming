#include <unistd.h>
#include <fcntl.h>
// Да се напише програма на C, която реализира командата cmp -s файл1 файл2
int main(int argc, char const *argv[])
{
    // cmp -s: Returns only an exit value. 
    // A value of 0 indicates identical files; 
    // value of 1 indicates different files; 
    // a value of 2 indicates inaccessible file or a missing option.

    if (argc < 2) 
    {
        write(STDERR_FILENO, "Missing arguments", 18);
        return 2;
    }

    int fd1 = open(argv[1], O_RDONLY);
    int fd2 = open(argv[2], O_RDONLY);

    if (fd1 == -1 || fd2 == -1) 
    {
        perror("Error");
        return 2;
    }

    char buff1[1];
    char buff2[1];

    if (lseek(fd1, 0, SEEK_END) != lseek(fd2, 0, SEEK_END))
        return 1;

    while (read(fd1,buff1,1) > 0 && read(fd2,buff2,1) > 0) {
        if (buff1[0] != buff1[0])
            return 1;
    }

    return 0;
}
