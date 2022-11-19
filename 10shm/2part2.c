#include <unistd.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/ipc.h>
// Да се напише програма на C, която създава 
// сегмент обща памет и записва текст в него. 
// Друга програма присъединява същия сегмент, 
// прочита текста, извежда го на екрана и унищожава сегмента.
//READER
int main(int argc, char const *argv[])
{
    int shmid = shmget((key_t)25362, 1024, 0);
    if (shmid == -1)
        perror("Error1");

    char* ptr = shmat(shmid, 0, 0);
    if (ptr == (char *)-1)
        perror("Error2");
    
    write(1,ptr,1024);

    shmdt(ptr);
    shmctl(shmid,IPC_RMID, 0);
    return 0;
}
