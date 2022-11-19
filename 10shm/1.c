#include <unistd.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/ipc.h>
 // Да се напише програма на C, 
    // която създава сегмент обща памет, 
    // записва текст в него, след това го прочита, 
    // извежда го на екрана и унищожава сегмента.
int main(int argc, char const *argv[])
{
   int shmid = shmget((key_t)2905200, 1024, IPC_CREAT|0644);
   if (shmid == -1) {
    write(2, "Error opening/creating shared memory segment.\n", 47);
    return -1;
   }

   char* ptr = shmat(shmid, NULL, 0);
   if(ptr == (void *)-1) {
    write(2, "Error attaching shared memory block\n", 37);
    return -1;
   }

    char str[] = "I'm text in the shared memory.\n";
    ptr = str;

    write(1, ptr, sizeof(str));

    shmdt(ptr);
    shmctl(shmid,IPC_RMID, NULL);

    return 0;
}
   
