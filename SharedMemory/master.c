#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>

#include "semaphore.h"
#include "sharedmem.h"

int main(int argc, char** argv)
{
	int i=0, prods=0, cons=0, semid=0, shmid=0, cc=0;
	void* Memory=NULL;
	if(argc<3)
	{
		puts("No arguments provided");
		exit(1);
	}
	prods=atoi(argv[1]);
	cons=atoi(argv[2]);
	semid=createSem();
	initializeSem(semid);
	shmid=createShm(92);
	Memory=linkShm(shmid);
	memset(Memory,0,92);
	for(i=0;i<prods;i++)
	{
		switch(fork())
		{
		case -1:
			perror("fork ERROR");
			exit(1);
			break;
		case 0:
			execl("./multiprod.exe","multiprod.exe",(char*) NULL);
			perror("execl error");
			_exit(2);
			break;
		default:
			break;
		}
	}
	for(i=0;i<cons;i++)
	{
		switch(fork())
		{
		case -1:
			perror("fork ERROR");
			exit(1);
			break;
		case 0:
			execl("./multikons.exe","multikons.exe",(char*) NULL);
			perror("execl error");
			_exit(2);
			break;
		default:
			break;
		}
	}
	while(wait(NULL)!=-1);
//	puts("Cleaning up");
	unlinkShm(Memory);
	removeSem(semid);
	removeShm(shmid);
	return 0;
}