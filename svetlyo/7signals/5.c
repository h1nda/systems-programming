#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include <stdio.h>
// Да се напише програма на C, която постоянно увеличава брояч, 
// през една секунда извежда стойността му на екрана, 
// а при натискане на Ctrl+C го нулира и продължава.
int count = 0;
int alarm_flag = 0;
void handler_sigalrm(int signum) {
    printf("Counter is %d\n", count);
    alarm_flag = 0;

}
void handler_sigint(int signum) {
    count = 0;
    write(1, "Counter reset.\n",16);

}

int main(int argc, char const *argv[])
{
    signal(SIGALRM, &handler_sigalrm);

    signal(SIGINT, &handler_sigint);

    while (1) {
        if (!alarm_flag) {
            alarm(1);
            alarm_flag = 1;
        }
        count++;
    }
    return 0;
}
