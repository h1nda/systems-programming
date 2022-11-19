#include <unistd.h>
#include <fcntl.h>
#include <sys/sem.h>
#include <stdio.h>
#include <sys/ipc.h>
// Да се напише програма на C, която създава семафор, инициализира го с 1,
// след това прочита стойността, извежда я на екрана и унищожава семафора.

int main(int argc, char const *argv[])
{
    int semid = semget((key_t)1231, 1, IPC_CREAT | 0644);

    
    // union semun
    // {
    //     int val;
    //     struct semid_ds *buf;
    //     unsigned short *array;
    // } arg;

    // arg.val = 1;

    // semctl(semid, 0, SETVAL, arg);


    //increment
    struct sembuf sb;
    sb.sem_num = 0;
    sb.sem_op = 1;
    sb.sem_flg = 0;
    semop(semid, &sb, 1);

    int val = semctl(semid, 0, GETVAL, NULL);

    printf("The value of the semaphore is %d\n", val);

    semctl(semid, NULL, IPC_RMID, NULL);
    return 0;
}
