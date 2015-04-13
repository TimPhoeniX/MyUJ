#include<unistd.h>
#include<stdio.h>
#include<signal.h>
#include<stdlib.h>

void sigIntHandler(int sig)
{
	puts("Otrzymano SIGINT");
	exit(EXIT_SUCCESS);
}
void sigQuitHandler(int sig)
{
	puts("Otrzymano SIGQUIT");
	exit(EXIT_SUCCESS);
}

int main(int argc, char **argv)
{
	if(argc>=2)
	{
		switch(atoi(argv[1]))
		{
			case 1:
				if (signal(SIGQUIT,sigQuitHandler) == SIG_ERR)
				{
					perror("Problem z SIGQUIT");
					exit(EXIT_FAILURE);
				}
				if (signal(SIGINT,sigIntHandler) == SIG_ERR)
				{
					perror("Problem z SIGINT");
					exit(EXIT_FAILURE);
				}
				break;
			case 2:
				if (signal(SIGQUIT,SIG_IGN) == SIG_ERR)
				{
					perror("Problem z SIGQUIT");
					exit(EXIT_FAILURE);
				}
				if (signal(SIGINT,SIG_IGN) == SIG_ERR)
				{
					perror("Problem z SIGINT");
					exit(EXIT_FAILURE);
				}
				break;
			default:
				if (signal(SIGQUIT,SIG_IGN) == SIG_ERR)
				{
					perror("Problem z SIGQUIT");
					exit(EXIT_FAILURE);
				}
				if (signal(SIGINT,sigIntHandler) == SIG_ERR)
				{
					perror("Problem z SIGINT");
					exit(EXIT_FAILURE);
				}
				break;
		}
	}
	else
	{
		if (signal(SIGQUIT,SIG_IGN) == SIG_ERR)
		{
			perror("Problem z SIGQUIT");
			exit(EXIT_FAILURE);
		}
		if (signal(SIGINT,sigIntHandler) == SIG_ERR)
		{
			perror("Problem z SIGINT");
			exit(EXIT_FAILURE);
		}
	}
	
	pause();

	exit(0);
}