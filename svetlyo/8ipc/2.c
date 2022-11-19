#include <unistd.h>
#include <fcntl.h>  
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
// Да се напише програма на C, която създава сегмент обща памет, 
// прочита информацията за права и собственост и 
// ги извежда на стандартния изход. 
// Променя собствеността и правата на достъп и отново извежда информацията. 
// Накрая изтрива общата памет.
int main(int argc, char const *argv[])
{
    int shmd = shmget((key_t)181, 1024, IPC_CREAT|O_EXCL|0644);

    if (shmd == -1)
        perror("Error");

    struct shmid_ds buf;

    if (shmctl(shmd,IPC_STAT,&buf) == -1)
        perror("Error");
    
    printf("Owner uid is %d, group owner id is %d.\nAccess permissions is %o\n",
    (int)buf.shm_perm.uid, (int)buf.shm_perm.gid, buf.shm_perm.mode);

    buf.shm_perm.gid = 6969;
    buf.shm_perm.mode = 0664;

    if (shmctl(shmd,IPC_SET,&buf) == -1)
        perror("Error");

    if (shmctl(shmd,IPC_RMID, NULL)) {
        printf("Successfully destroyed shared memory\n");
    }

    return 0;
}
