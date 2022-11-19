#include <unistd.h>
#include <fcntl.h>
#include <sys/sem.h>
#include <stdio.h>
#include <sys/ipc.h>
// Да се напише програма на C, която синхронизира 2 процеса чрез семафор. 
// Всеки от процесите отваря файл без флага O_APPEND и 
// неколкократно добавя текст по следния начин - позиционира се в края, 
// изчаква няколко секунди и пише.

int main(int argc, char const *argv[])
{
    int fd = open("file", O_CREAT|O_WRONLY, 0644);
    int semid = semget((key_t)5741, 1, IPC_CREAT|0644);

    while (1) {
        struct sembuf sb[2];
        sb[0].sem_op = 0; //wait for 0
        sb[1].sem_op = 1; //then atomically increment to 1
        semop(semid, sb, 2);

        //task
        lseek(fd, 0, SEEK_END);
        write(fd, "Process one has written to file.\n", 34);

        // decrement sem back to 0
        sb[0].sem_op = -1;
        semop(semid, &sb[0], 1);
        sleep(4);
        
    }
    semctl(semid, 0, IPC_RMID, NULL);
    return 0;
}
