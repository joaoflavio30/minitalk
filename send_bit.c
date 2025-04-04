void    send_bit(int c)
{
    int i = 8;
    while (--i >= 0)
    {
        if ((c >> i) & 1)
            kill(pid, SIGUSR2);
        else
            kill(pid, SIGUSR1);
        usleep(100);
    }
}