#include <unistd.h>
#include <fcntl.h>
#include <sys/sem.h>
#include <stdio.h>
#include <sys/ipc.h>
// Да се напише програма на C, която синхронизира 2 родствени процеса чрез семафор. 
// Двата процеса работят едновременно и трябва да изведат 
// текст на стандартния изход в определен ред. 
// Единия чака няколко секунди и пише. Другия пише след него.
int main(int argc, char const *argv[])
{
    int semid = semget((key_t)4751, 1, IPC_CREAT|0644);
    int pid = fork();

    struct sembuf sb[2];

    if (pid == 0) {
        //child
        while (1) {
            sb[0].sem_op = 0; // wait for zero
            sb[1].sem_op = 1; //increment to one
            semop(semid, sb, 2); //atomic
            //does task
            write(1, "Child's writing to the terminal.\n", 34);

            sb[0].sem_op = -1; // decrements semval (back to 0)
            semop(semid,&sb[0], 1);
        }

    } else {
        //parent
        while (1) {
            sb[0].sem_op = 0; // wait for zero
            sb[1].sem_op = 1; //increment to one
            semop(semid, sb, 2); //atomic
            //does task
            write(1, "Parent's writing to the terminal.\n", 34);

            sb[0].sem_op = -1; // decrements semval (back to 0)
            semop(semid, &sb[0], 1);
        }
    }
    semctl(semid, NULL, IPC_RMID, NULL);
    return 0;
}
