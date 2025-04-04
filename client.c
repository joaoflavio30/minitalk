#include "mini_talk.h"
void    send_bit(int c, int pid)
{
    int i = 8;
    while (--i >= 0)
    {
        if ((c >> i) & 1)
            kill(pid, SIGUSR2);
        else
            kill(pid, SIGUSR1);
        usleep(5000);
    }
}

int main(int argc, char **argv)
{
    if (argc != 3)
    {
        return (1);
    }
    int i = -1;
    int server_pid = atoi(argv[1]);
    while(argv[2][++i])
    {
        send_bit(argv[2][i] , server_pid);
    }
    return (0);
}