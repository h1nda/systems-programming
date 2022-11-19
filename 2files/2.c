#include <unistd.h>
#include <fcntl.h>
// Да се напише програма на C, която отваря файл за писане, 
// затваря стандартния изход, 
// дублира дескриптора на отворения файл и пише на стандартния изход.
int main(int argc, char const *argv[])
{
    int fd = open("file.txt", O_WRONLY);

    close(1);

    dup(fd); 

    write(1, "I'm now the standard output!\n",30);

    close(fd);
    return 0;
}
