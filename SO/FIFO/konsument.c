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
	char *name=(argc==2 ? argv[1] : "mypipe");
	int pipe=open(name,O_RDONLY,0644);
	if(pipe==-1)
	{
		perror("open ERROR");
		exit(1);
	}
	read_pipe(pipe);
	if(close(pipe))
	{
		perror("close ERROR");
		exit(1);
	}
	if(unlink(name))
	{
		perror("unlink ERROR");
		exit(1);
	}
	return 0;
}