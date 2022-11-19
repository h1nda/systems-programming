#include <unistd.h>
#include <fcntl.h>  
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <string.h>
// Да се напише програма на C, която създава опашка, 
// изпраща съобщение в нея, 
// след това го прочита и го извежда на стандартния изход.
struct mymsg {
        long int mtype;
        char mtext[256];
    };

int main(int argc, char const *argv[])
{
    int mqid = msgget((key_t)325231, IPC_CREAT|0644|O_EXCL);

    struct mymsg msg;
    strcpy(msg.mtext, "I'm a message being sent in the queue.\n");
    msg.mtype = 1;

    if(msgsnd(mqid, (void *)&msg, sizeof(msg.mtext), 0) == -1)
        perror("error");

    struct mymsg rcvd;
    long int huh;

    if (msgrcv(mqid, (void *)&rcvd, BUFSIZ, 0, 0) == -1)
        perror("error");

    printf("Received message: %s", rcvd.mtext);

    msgctl(mqid, IPC_RMID, 0);

    return 0;
}
