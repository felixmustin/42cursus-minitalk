#include "utils.h"

unsigned char reverse(unsigned char b) {
   b = (b & 0xF0) >> 4 | (b & 0x0F) << 4;
   b = (b & 0xCC) >> 2 | (b & 0x33) << 2;
   b = (b & 0xAA) >> 1 | (b & 0x55) << 1;
   return b;
}

void sig_handle(int signum, siginfo_t *info, void *tmp)
{
    static int i;
    static unsigned char c;

    (void)tmp;
    if (signum == SIGUSR1)
        c |= 1 << i;
    i++;
    if (i == 8)
    {
        if (!c)
        {
            kill(info->si_pid, SIGUSR2);
            return ;
        }
        c = reverse(c);
        ft_putchar(c);
		kill(info->si_pid, SIGUSR1);
        c = 0;
        i = 0;
    }
}

int main(void)
{
    int pid;

    struct sigaction	sig_act;

	sig_act.sa_sigaction = sig_handle;
	sig_act.sa_flags = SA_SIGINFO;

	pid = getpid();
    ft_putstr("Server Launched\nPID : ");
	ft_putnbr(pid);
    ft_putstr("\n");

	sigaction (SIGUSR1, &sig_act, NULL);
	sigaction (SIGUSR2, &sig_act, NULL);
	while (1)
		pause();
}