#include "utils.h"

void sig_handler(int sig_num)
{
    if (sig_num == SIGUSR1)
        write(1, "Message received\n", 17);
    else if (sig_num == SIGUSR2)
        write(1, "Message error\n", 14);
}

void send_sig(int pid, int n)
{
    if (n == 1)
    {
        if (kill (pid, SIGUSR1) == -1)
            ft_putstr("Bad PID\n");
    }
    else if (n == 0)
    {   
        if (kill (pid, SIGUSR2) == -1)
            ft_putstr("Bad PID\n");
    }
}

void convert_char(int pid, unsigned int dec)
{
    int ref;

    ref = 128;
    while (ref > 0)
    {
        if ((dec & ref) == 0)
            send_sig(pid, 0);
        else
            send_sig(pid, 1);
        ref  >>= 1;
        usleep(100);
    }
}

void convert_string(int pid, char *str)
{
    int i;
    unsigned int dec;

    i = 0;
    while (str[i])
    {
        dec = (unsigned int)str[i];
        convert_char(pid, dec);
        i++;
    }
}

int main(int argc, char **argv)
{
    int pid;
    struct sigaction sig_act;

    sig_act.sa_handler = sig_handler;
    sigaction (SIGUSR1, &sig_act, NULL);
    if (argc < 3)
        ft_putstr("Not enough arguments");
    else if (argc > 3)
        ft_putstr("Too much arguments");
    else
    {
        pid = ft_atoi(argv[1]);
        convert_string(pid, argv[2]);
    }
}