#include <unistd.h>
#include <fcntl.h>
// Да се напише програма на C, която реализира командата head файл
int main(int argc, char const *argv[])
{
    // head: изпечатва на стандартния изход първите 10 реда
    int fd = open(argv[1], O_RDONLY);
    if (fd == -1) {
        perror("Error");
        return -1;
    }

    char buf[1];
    int counter = 0;
    while(read(fd, buf, 1) > 0 ) {
        if (buf[0] == '\n')
            counter++;

        if (counter == 10) {
            write(STDOUT_FILENO, "\n", 1);
            break;
        }

        write(STDOUT_FILENO, buf, 1);

    }


    return 0;
}
