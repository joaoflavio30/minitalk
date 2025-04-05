#include "mini_talk.h"
volatile sig_atomic_t ack = 0;

void ack_handler(int sig)
{
    (void)sig;
    ack = 1;
}

void    send_bit(int c, int pid)
{
    int i = 8;
    while (--i >= 0)
    {
        ack = 0;
        if ((c >> i) & 1)
            kill(pid, SIGUSR2);
        else
            kill(pid, SIGUSR1);

        
        while (!ack)
            pause();
    }
}

int main(int argc, char **argv)
{
    if (argc != 3)
    {
        return (1);
    }
    struct sigaction sa;
    sa.sa_handler = ack_handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sigaction(SIGUSR1, &sa, NULL);
    int i = -1;
    int server_pid = atoi(argv[1]);
    while(argv[2][++i])
    {
        send_bit(argv[2][i] , server_pid);
    }
    return (0);
}