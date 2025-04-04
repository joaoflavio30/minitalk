void bit_receiver(int sigum)
{
    static char c = 0;
    int  bit;
    static int     i = 0;

    if (signum == SIGUSR1)
        bit = 0;
    else if (signum == SIGUSR2)
        bit = 1;
    c = (c << 1) | bit;
    i++;
    if (i == 8)
    {
        write(1, &c, 1);
        i = 0;
        c = 0;
    }
}