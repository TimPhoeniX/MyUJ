#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<sys/wait.h>
#include "semaphore.h"
#include "sharedmem.h"

int main(void)
{
	int sourcedes=0,semid=0,shmid=0,buffcount=0,state=0, *counter=NULL;
	char *buffer=NULL, *completed;
	semid=createSem();
	initializeSem(semid);
	shmid=createShm(85);
	buffer=(char*)linkShm(shmid);
	counter=(int*)(buffer+80); /*licznik umieszczonych w pamięci dzielonej segmentów*/
	completed=(char*)(buffer+84); /*Informacja dla konsumenta, kiedy może zakończyć działanie*/
	memset(buffer,0,85);
//	printf("Prod - Semid=%d, Shmid=%d, Buffer=%p\n",semid,shmid,buffer);
	switch(fork())
	{
	case -1:
		perror("fork ERROR");
		exit(1);
		break;
	case 0:
		execl("./konsument.exe", "konsument.exe", (char*) NULL);
		perror("execl error");
		_exit(2);
		break;
	default:
		break;
	}
	if((sourcedes=open("source.txt",O_RDONLY,0644))==-1)
	{
		perror("open ERROR");
		exit(1);
	}
	
	while(1)
	{
		PB(semid);
		while(WaitP(semid)==0); /*Synchronizacja z konsumentem*/
		memset(buffer+buffcount*8,0,8);
		if((state=read(sourcedes,buffer+buffcount*8,8))==-1)
		{
			perror("read ERROR");
			exit(1);
		}
		++buffcount;
		if(buffcount>9) buffcount=0;
		if(state==0)
		{
			(*completed)=1;
			VB(semid);
			break;
		}
		else
		{
			++(*counter);
			VB(semid);
		}
	}
	if(close(sourcedes)==-1)
	{
		perror("close ERROR");
		exit(1);
	}
	while(wait(NULL)!=-1);
	removeSem(semid);
	unlinkShm(buffer);
	removeShm(shmid);
	return 0;
}