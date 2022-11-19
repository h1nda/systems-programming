#include <unistd.h>
#include <fcntl.h>  
#include <sys/ipc.h>
#include <sys/sem.h>
#include <stdio.h>
#include <stdlib.h>
// Да се напише програма на C, която създава семафор с ключ, 
// подаден като параметър и извежда номера му на стандартния изход. 
// Друга програма получава същия ключ като параметър, 
// извежда номера(id) на семафора на стандартния изход и 
// след това изтрива семафора.
int main(int argc, char const *argv[])
{
    if (argc < 2) 
        write(2, "Minimum argument count is 1\n",29);
    
    int num = strtol(argv[1], NULL, 10);

    int semid = semget((key_t)num, 1, IPC_CREAT|0644);
    printf("Semaphore set id is %d\n", semid);

    struct sembuf sops[1];
    semop(semid, sops, 1);

    printf("The semaphore ID is %d\n", sops[0].sem_num);

    return 0;
}
