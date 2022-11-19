#include <unistd.h>
#include <fcntl.h>
// Да се напише програма на C, която отваря файл за четене, 
// дублира дескриптора, последователно чете от двата дескриптора 
// и извежда прочетеното на екрана. 
// Затваря оригиналния дескриптор и продължава да чете от дублирания.
int main(int argc, char* const argv[]) {
    int fd = open("file.txt", O_RDONLY);

    int dfd = dup(fd);

    char buff[1];
    
    read(fd, buff, 1);
    write(1, buff, 1);

    read(dfd, buff, 1);
    write(1,buff,1);

    close(fd);

    while (read(dfd,buff,1)) {
        write(1,buff,1);
    }
}