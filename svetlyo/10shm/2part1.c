#include <unistd.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/ipc.h>
// Да се напише програма на C, която създава 
// сегмент обща памет и записва текст в него. 
// Друга програма присъединява същия сегмент, 
// прочита текста, извежда го на екрана и унищожава сегмента.

char* strcpy(char* dest, const char* src) {
    char* saved = dest;
    while (*src) {
        *dest++ = *src++;
    }
    *dest = 0;
    return saved;
}
//CREATOR
int main(int argc, char const *argv[])
{
    int shmid = shmget((key_t)25362, 1024, IPC_CREAT|0644);
    if (shmid == -1)
        perror("Error1");

    char* ptr = shmat(shmid,0, 0);
    if (ptr == (void *)-1)
        perror("Error2");

    char str[] = "Text in the shared memory.\n";

    strcpy(ptr,str);
 
    shmdt(ptr);
    return 0;
}

