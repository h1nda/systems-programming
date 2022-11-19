#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
// Да се напише програма на C, която синхронизира два родствени процеса чрез съобщения.
// Двата процеса пишат текст на стандартния изход в следния ред -
// единия, другия, отново първия. Процеса който пише пръв,
// изчаква няколко секунди преди да пише.
struct mymsg
{
    long int mtype;
    char *msg;
};
int main(int argc, char const *argv[])
{
    int mqid = msgget((key_t)123, IPC_CREAT| 0644);
    if (mqid == -1)
    {
        perror("error");
    }

    // set message queue size to 14
    struct msqid_ds buf;
    msgctl(mqid, IPC_STAT, &buf);
    buf.msg_qbytes = 14;
    msgctl(mqid, IPC_SET, &buf);

    // create processes
    int pid = fork();

    if (pid == -1)
    {
        perror("Error");
    }
    else if (pid == 0)
    {
        
        // child process
        //  first writer
        struct mymsg snd_msg;
        snd_msg.mtype = 1;
        snd_msg.msg = "I'm done. Go\n";
        printf("Size of mq in bytes is %d\n", (int)buf.msg_qbytes);
        sleep(10);
        while (1)
        {
            if (msgsnd(mqid, (void *)&snd_msg, 14, 0) == -1)
            {
                perror("error sending message");
            }
            write(1, "I'm writing (c).\n", 18);
        }
    }
    else
    {
        // parent process
        struct mymsg rcvd_msg;
        while (1)
        {
            if (msgrcv(mqid, (void *)&rcvd_msg, 14, 0, 0) == -1)
            {
                perror("error receiving message\n");
            }
            write(1, "I'm writing (p).\n", 18);
        }

         msgctl(mqid,IPC_RMID, NULL);
    }
    return 0;
}
