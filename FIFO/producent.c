#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<time.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>
#include "pipe.h"

int main(int argc,char **argv)
{
	int pipe=0;
	char *name=(argc==2 ? argv[1] : "mypipe");
	if(argc==1)
		if(mkfifo(name,0644)==-1)
		{
			perror("mkfifo ERROR");
			exit(1);
		}
	pipe=open(name,O_WRONLY,0644);
	if(pipe==-1)
	{
		perror("open ERROR");
		exit(1);
	}
	write_pipe(pipe);
	sleep(1);
	if(close(pipe))
	{
		perror("close ERROR");
		exit(1);
	}
	return 0;
}