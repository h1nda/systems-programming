#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include <stdio.h>
// Да се напише програма на C, която постоянно увеличава брояч, 
// през една секунда извежда стойността му на екрана, 
// а при натискане на Ctrl+C го нулира и продължава.

int count = 0;
int alarm_flag = 0;

void handler_sigalrm(int signum)
 {
    alarm_flag = 1;
 }
int main(int argc, char const *argv[])
{
    struct sigaction sa;

    sa.sa_handler = &handler_sigalrm;
    sa.sa_flags = 0;
    sigaction(SIGALRM, &sa, NULL);

    alarm(1);

    while (1) {
        count++;

        if (alarm_flag == 1) {
            char buffer[80];                          
            int LengthUsed = sprintf(buffer, "%d", count); 
            write(1, buffer, LengthUsed);   
            alarm_flag = 0;
            alarm(1);
        }
    }
    
    return 0;
}
