#include <unistd.h>
#include <fcntl.h>
// Да се напише програма на C, която реализира командата cp файл1 файл2
int main(int argc, char const *argv[])
{
    if (argc < 3) {
        char* errormsg = "Error: Arguments are not enough.";
        write(STDERR_FILENO, errormsg, 33);
        return -1;
    }
    
    int fd1 = open(argv[1], O_RDONLY);
    int fd2 = open(argv[2], O_CREAT|O_TRUNC|O_WRONLY, 0644);

    char buff[1];

    while (read(fd1, buff, 1) > 0) {
        write(fd2, buff, 1);
    }
    return 0;
}
