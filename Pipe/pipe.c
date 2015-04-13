#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<time.h>
#include<sys/types.h>
#include<sys/wait.h>

void read_pipe(int pipedes)
{
	char c=0;
	FILE *copy=fopen("copy.txt","w");
	srand(time(NULL)-5000);
	if(copy==NULL)
	{
		perror("fopen Error");
		exit(1);
	}
	while(read(pipedes,&c,1)==1)
	{
		fputc(c,copy);
		usleep(rand()%10000);
	}
	fclose(copy);
}

void write_pipe(int pipedes)
{
	char c=0;
	FILE *source=fopen("source.txt","r");
	srand(time(NULL));
	if(source==NULL)
	{
		perror("fopen Error");
		exit(1);
	}
	while((c=fgetc(source))!=EOF)
	{
		if(write(pipedes,&c,1)==-1)
		{
			perror("write error");
			exit(1);
		}
		usleep(rand()%10000);
	} 
	fclose(source);
}
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