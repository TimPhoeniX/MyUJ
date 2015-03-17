#include<unistd.h>
#include<stdio.h>
#include<signal.h>
#include<stdlib.h>

void sighandler(int sig)
{
	puts("Otrzymano SIGINT");
	exit(EXIT_SUCCESS);
}

int main()
{
	if (signal(SIGQUIT,SIG_IGN) == SIG_ERR)
	{
		perror("Problem z SIGQUIT");
		exit(EXIT_FAILURE);
	}
	if (signal(SIGINT,sighandler) == SIG_ERR)
	{
		perror("Problem z SIGINT");
		exit(EXIT_FAILURE);
	}
	
	pause();

	exit(0);
}