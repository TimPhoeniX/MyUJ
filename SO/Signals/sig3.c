#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<signal.h>

int main()
{
	int i = 0;
	for (i = 0; i < 6;i++)
	{
		switch (fork())
		{
		case -1:
			perror("fork ERROR");
			exit(1);
			break;
		case 0:
			execl("./sig1.exe", "sig1.exe", (char*)NULL);
			perror("execl error");
			_exit(2);
			break;
		default:
			break;
		}
	}
	if (signal(SIGINT,SIG_IGN) == SIG_ERR)
	{
		perror("Problem z SIGINT");
		exit(EXIT_FAILURE);
	}
	sleep(1);
//	kill(-getpgid(getpgrp()),SIGINT);
	kill(0,SIGINT);
	while (wait(NULL) != -1);
	exit(0);
}