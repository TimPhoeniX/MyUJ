#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
int main()
{
	int status_location=0, i=0;
	printf("UID %d | GID %d | PID %d | PPID %d | PGID %d\n",getuid(),getgid(),getpid(),getppid(),getpgid(getpgrp()));
	sleep(1);
	for(i=0;i<3;i++)
	{
		switch(fork())
		{
			case -1:
				perror("fork ERROR");
				exit(1);
				break;
			case 0:
//				sleep(1);
				printf("UID %d | GID %d | PID %d | PPID %d | PGID %d\n",getuid(),getgid(),getpid(),getppid(),getpgid(getpgrp()));
				sleep(1);
				break;
			default:
//				while(wait(&status-location)!=-1);
//				sleep(0);
				break;
		}
//	sleep(1);
	}		
	while(wait(&status_location)!=-1);
//		sleep(1);
	return 0;
}