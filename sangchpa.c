#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

SIGQUIT, SIGINT => exec은 무조건 죽음 => SIGCHLD 발생?
signal(SIGCHLD, child_handler); => 개행이나 QUIT 출력?
signal(SIGINT, signal_handler);
signal(SIGQUIT, signal_handler);



void	signal_handler(int signo)
{
	if (signo == SIGINT)
	{
		kill(0, SIGUSR2);
		kill(0, SIGUSR1);
		write(0, "\n", 1);
	}
	else if (signo == SIGQUIT)
	{
		write(1, "\r", 1);
		kill(0, SIGCONT);
		return ;
	}
	else if (signo == SIGUSR1)
	{
		write(1, "\n", 1);
		exit(0);
	}
	else if (signo == SIGUSR2)
	{
		g_exit_status_code = 1;
	}
}

void	signal_fatal_error(int signo)
{
	if (signo == SIGUSR1)
	{
		kill(0, SIGUSR2);
	}
	else if (signo == SIGUSR2)
	{
		g_exit_status_code = 130;
	}
}