#include <unistd.h>
#include <fcntl.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <stdio.h>

// Да се напише програма на C, която създава опашка и поражда процес. 
// Единия процес чете съдържанието на файл, 
// чието име е подадено като параметър в командния ред и го праща в опашката. 
// Другия процес получава съобщения от опашката и ги извежда на стандартния изход.
struct mymsg {
    long int type;
    char msg[8192];
};

int main(int argc, char const *argv[])
{
    int mqid = msgget((key_t)45874, IPC_CREAT|0644);
    if (mqid == -1) 
        perror("Error");

    int pid = fork();
    if (pid == -1)
        perror("Error");
    
    if (pid == 0) {
        //child process
        struct mymsg rcvd_msg;

        if (msgrcv(mqid, (void *)&rcvd_msg, 8192, 0, 0) == -1)
            perror("Error");
        
        printf("%s", rcvd_msg.msg);

        msgctl(mqid, IPC_RMID, 0);

    } else {
        //parent process
        int fd = open(argv[1], O_RDONLY);
        if (fd == -1) 
            perror("Error");
        
        off_t filesize = lseek(fd, 0, SEEK_END); // get filesize
        lseek(fd,0,SEEK_SET); // reposition pointer

        char buf[filesize+1];
        if (read(fd, &buf, sizeof(buf)) == -1)
            perror("Error");

        struct mymsg msg_snd;
        msg_snd.type = 1;
        strcpy(msg_snd.msg, buf);

        if (msgsnd(mqid, (void *)&msg_snd, sizeof(msg_snd.msg), 0) == -1)
            perror("error");
    }
    return 0;
}

