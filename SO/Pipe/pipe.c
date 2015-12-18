#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<time.h>
#include<sys/types.h>
#include<sys/wait.h>
#include "pipe.h"

void read_pipe(int pipedes)
{
	char c=0;
	int state=0;
	FILE *copy=fopen("copy.txt","w");
	srand(time(NULL)-5000);
	if(copy==NULL)
	{
		perror("fopen ERROR");
		exit(1);
	}
	while((state=read(pipedes,&c,1)))
	{
		if(state==-1)
		{
			perror("read ERROR");
			exit(1);
		}
		fputc(c,copy);
		if(ferror(copy))
		{
			perror("fputc ERROR");
			exit(1);
		}
		usleep(rand()%2000);
	}
	if(fclose(copy))
	{
		perror("fclose ERROR");
		exit(1);
	}
}

void write_pipe(int pipedes)
{
	char c=0;
	FILE *source=fopen("source.txt","r");
	srand(time(NULL));
	if(source==NULL)
	{
		perror("fopen ERROR");
		exit(1);
	}
	while((c=fgetc(source))!=EOF)
	{
		if(write(pipedes,&c,1)==-1)
		{
			perror("write ERROR");
			exit(1);
		}
		usleep(rand()%2000);
	}
	if(ferror(source))
	{
		perror("fgetc ERROR");
		exit(1);
	}
	if(fclose(source))
	{
		perror("fclose ERROR");
		exit(1);
	}
}