#include <unistd.h>
#include <fcntl.h>
int main(int argc, char const *argv[])
{
    if (argc < 2) {
        write(2, "File not provided.", 19);
        return -1;
    }

    int fd = open(argv[1], O_RDONLY);
    if (fd == -1)
        perror();

    int word_c = 0;
    int lines_c = 0;
    int char_c = 0;

    char buff[1];
    while (read(fd, buff,1) > 0) {
        if (buff[0] == '\t' || buff[0] == ' ')
            word_c++;
        
        if (buff[0] == '\n')
            lines_c++;
        
        else
            char_c++;
    }

    char sth = lines_c +'0';
    if (write(1, sth, sizeof(sth)) <= 0)
        perror();
    return 0;
}
