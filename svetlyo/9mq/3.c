#include <unistd.h>
#include <fcntl.h>  
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <string.h>
// Да се напише програма на C, която създава опашка и поражда процес. 
// Единия процес чете текст от стандартния вход и го праща в опашката.
//  Другия процес получава съобщения от опашката и ги записва във файл, 
//  чието име е подадено като параметър в командния ред. 
// (Следете съдържанието на файла по време на изпълнение, например от друг терминал)
struct mymsg {
    long int type;
    char msg[4096];
};

int main(int argc, char const *argv[])
{
    int pid = fork();
    if (pid == -1)
        perror("error3");

    int mqid = msgget((key_t)6452, IPC_CREAT|0644);
    if (mqid == -1)
        perror("error");

    if (pid == 0) {
        // child

        int fd = open("dump.txt", O_CREAT|O_TRUNC|O_WRONLY, 0644);

        while (1) {
            struct mymsg rcvd_msg;
            if (msgrcv(mqid, (void *)&rcvd_msg, 4096, 0, 0) == -1) {
                // printf("Message size is: %d", sizeof(rcvd_msg.msg));
                perror("Error1");
            } else {
                write(fd, &rcvd_msg.msg, strlen(rcvd_msg.msg)+1);
            }

            // write(1, &rcvd_msg.msg, sizeof(&rcvd_msg.msg));
        }

        msgctl(mqid, IPC_RMID, 0);

    } else {
        // parent
        char c;
        while (1) {
            char line[4096];
            int i = 0;


            // reads until new line in terminal
            while (read(0, &c, 1) > 0) {
                line[i++] = c;
                if (c == '\n') {
                    line[i] = '\0';
                    break;
                    // write(1,"Found newline", 14);
                }
            }
            // write the line to the queue
            struct mymsg snt_msg;
            snt_msg.type = 1;
            strcpy(snt_msg.msg, line);
            if (msgsnd(mqid, (void *)&snt_msg, i+1, 0) == -1) {
                perror("error2");
            }
        }

    }
    

    return 0;
}
