#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>

#include "semaphore.h"
#include "sharedmem.h"

int main(int argc, char** argv)
{
	int i=0, total=0, semid=0, shmid=0;
	char *Total=NULL, ID[20];
	if(argc<2)
	{
		puts("No argument provided");
		exit(1);
	}
	Total=argv[1];
	total=atoi(argv[1]);
	semid=createSem();
	initializeSem(semid);
	shmid=createShm(total*86);
	for(i=0;i<total;i++)
	{
		snprintf(ID,20,"%d",i);
		switch(fork())
		{
		case -1:
			perror("fork ERROR");
			exit(1);
			break;
		case 0:
			execl("./multiprod.exe","multiprod.exe",ID,Total,(char*) NULL);
			perror("execl error");
			_exit(2);
			break;
		default:
			break;
		}
		switch(fork())
		{
		case -1:
			perror("fork ERROR");
			exit(1);
			break;
		case 0:
			execl("./multikons.exe","multikons.exe",ID,Total,(char*) NULL);
			perror("execl error");
			_exit(2);
			break;
		default:
			break;
		}
	}
	while(wait(NULL)!=-1);
	removeSem(semid);
	removeShm(shmid);
	return 0;
}