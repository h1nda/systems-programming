#include <unistd.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <stdio.h>
#include <sys/ipc.h>
// Да се напише програма на C, която създава сегмент обща памет с размер int, 
// инициализиран с 0 и поражда процес. Двата процеса едновременно, 
// през различен интервал от време, увеличават числото, докато стане 100 
//  извеждат на екрана номера на процеса си и новата стойност.

int main(int argc, char const *argv[])
{
    int shmid = shmget((key_t)3257, sizeof(int), IPC_CREAT|0644);
    if (shmid == -1)
        perror("Error shared memory open/creation");

    int pid = fork();
    if (pid == -1)
        perror("Error fork");
    
    if (pid == 0) {
        // child;
        //sleep until parent puts i in the shared memory and increments it
        sleep(1);
        int* q = shmat(shmid, 0, 0);
        while (1) {
            (*q)++;
            printf("(c) Value of is %d\n", *q);
            sleep(3);
        }
    } else {
        // parent - gonna create the variable, then put it in the shared memory
        // write(1,"I'm here.", 10);
        int i = 0;
        int* p = shmat(shmid, 0, 0);
        *p = i;
        // write(1, "I've done my job.\n", 18);

        while (1) {
            sleep(3);
            (*p)++;
            printf("(p) Value of is %d\n", *p);
        }
    }

    shmctl(shmid,IPC_RMID, 0);

    return 0;
}
