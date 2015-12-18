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

int main(int argc, char** argv)
{
	int sourcedes=0,semid=0,shmid=0,buffcount=0,state=0, *counter=NULL,
		buffsize=8, ID=0, Total=0;
	char *buffer=NULL, *buffed_count=NULL, *completed;
	void *Memory=NULL;
	if(argc<3)
	{
		puts("No arguments provided");
		exit(1);
	}
	ID=atoi(argv[1]);
	Total=atoi(argv[2]);
	semid=getSem();
	shmid=accessShm(Total*86);
	Memory=linkShm(shmid);
	buffer=(char*)(Memory+86*ID);
	counter=(int*)(buffer+80); /*licznik pilnuje, żeby konsument nie umieszczał powtarzających się fragmentów pliku*/
	completed=(char*)(buffer+84); /*Informacja dla konsumenta, kiedy może zakończyć działanie*/
	buffed_count=(char*)(buffer+85);
	memset(buffer,0,86);
//	printf("Prod - ID=%d/%d, Semid=%d, Shmid=%d, Buffer=%p\n",ID,Total,semid,shmid,buffer);
	if((sourcedes=open("source.txt",O_RDONLY,0644))==-1)
	{
		perror("open ERROR");
		exit(1);
	}
	if(lseek(sourcedes,ID*buffsize,SEEK_CUR)==-1)
	{
		perror("lseek ERROR");
		exit(1);
	}
	while(1)
	{
		PB(semid);
		if(*buffed_count<10)
		{
			while(WaitP(semid)==0); /*Synchronizacja z resztą procesów*/
			memset(buffer+buffcount*buffsize,0,buffsize);
			if((state=read(sourcedes,buffer+buffcount*buffsize,buffsize))==-1)
			{
				perror("read ERROR");
				exit(1);
			}
			++buffcount;
			if(lseek(sourcedes,(Total-1)*buffsize,SEEK_CUR)==-1)
			{
					perror("lseek ERROR");
					exit(1);
			}
			if(buffcount>9) buffcount=0;
		}
		if(state==0)
		{
			(*completed)=1;
			VB(semid);
			break;
		}
		else
		{
			(*buffed_count)++;
			++(*counter);
			VB(semid);
		}
	}
	unlinkShm(Memory);
	if(close(sourcedes)==-1)
	{
		perror("close ERROR");
		exit(1);
	}
//	printf("Prod ID %d exitting\n",ID);
	return 0;
}