#include <unistd.h>
#include <fcntl.h>           /* For O_* constants */
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>

// Да се напише програма на C, която създава опашка, 
// прочита информацията за права и собственост и ги извежда на стандартния изход. 
// Променя собствеността и правата на достъп и отново извежда информацията. Накрая изтрива опашката.
int main(int argc, char const *argv[])
{
    int mqd = msgget((key_t)1113, 0644|IPC_CREAT);

    struct msqid_ds buf;

    msgctl(mqd, IPC_STAT, &buf);

    printf("Owner uid is %d, group owner id is %d.\nAccess permissions is %o\n",
    (int)buf.msg_perm.uid, (int)buf.msg_perm.gid, buf.msg_perm.mode);

    buf.msg_perm.mode = 0642;
    buf.msg_perm.gid = 6969;


    if (msgctl(mqd, IPC_SET, &buf) == -1)
        perror("Error");
        

    printf("Owner uid is %d, group owner id is %d.\nAccess permissions is %o\n",
    (int)buf.msg_perm.uid, (int)buf.msg_perm.gid, buf.msg_perm.mode);
    
    msgctl(mqd,IPC_RMID, NULL);

    return 0;
}
