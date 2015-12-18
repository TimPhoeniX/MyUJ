#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
int main(void)
{
	printf("UID %d | GID %d | PID %d | PPID %d | PGID %d\n",
			getuid(),getgid(),getpid(),getppid(),getpgid(getpgrp()));
	exit(0);
}