#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<time.h>
#include<sys/types.h>
#include<sys/wait.h>
#include "pipe.h"

int main()
{
	int pipedes[2];
	
	if(pipe(pipedes))
	{
		perror("pipe error");
		exit(1);
	}
	switch(fork())
	{
		case -1:
			perror("fork ERROR");
			exit(1);
			break;
		case 0:
			close(pipedes[1]);
			read_pipe(pipedes[0]);
			close(pipedes[0]);
			break;
		default:
			close(pipedes[0]);
			write_pipe(pipedes[1]);
			close(pipedes[1]);
			break;
	}
	while(wait(NULL)!=-1);
	return 0;
}