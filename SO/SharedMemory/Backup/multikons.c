#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>
#include "semaphore.h"
#include "sharedmem.h"

int main(int argc, char** argv)
{
	int copydes=0,semid=0,shmid=0,buffcount=0,loops=0,
		*counter=NULL, buffsize=8, ID=0, Total=0;
	char *buffer=NULL, *buffed_count=NULL, *completed=NULL;
	void *Memory=NULL;
	if(argc<3)
	{
		puts("No arguments provided");
		exit(1);
	}
	ID=atoi(argv[1]);
	Total=atoi(argv[2]);
	if((copydes=open("copy.txt",O_WRONLY|O_CREAT,0644))==-1)
	{
		perror("open ERROR");
		exit(1);
	}
	semid=getSem();
	shmid=accessShm(Total*86);
	Memory=linkShm(shmid);
	buffer=(char*)(Memory+86*ID);
	counter=(int*)(buffer+80);
	completed=(char*)(buffer+84);
	buffed_count=(char*)(buffer+85);
//	printf("Kons - ID=%d/%d, Semid=%d, Shmid=%d, Buffer=%p\n",ID,Total,semid,shmid,buffer);
	if(lseek(copydes,ID*buffsize,SEEK_CUR)==-1)
	{
		perror("lseek ERROR");
		exit(1);
	}
	while(1)
	{
		PB(semid);
//		printf("%d, %d, %d, %d, %d, %d\n",loops, *counter,*completed,*buffed_count, buffcount, ID);
		if(loops<(*counter))
		{
			if(*buffed_count>0)
			{
				while((*(buffer+buffcount*8+buffsize-1))==0) --buffsize;
				if(write(copydes,buffer+buffcount*8,buffsize)==-1)
				{
					perror("write ERROR");
					exit(1);
				}
				buffsize=8;
				++buffcount;
				if(buffcount>9) buffcount=0;
				++loops;
				if(lseek(copydes,(Total-1)*buffsize,SEEK_CUR)==-1)
				{
					perror("lseek ERROR");
					exit(1);
				}
				(*buffed_count)--;
			}
		}
		VB(semid);
//		if(loops>=*counter && *completed) break;
		if((*completed) && (*buffed_count==0)) break;
	}
	unlinkShm(Memory);
	if(close(copydes)==-1)
	{
		perror("close ERROR");
		exit(1);
	}
//	printf("Kons ID %d exitting\n",ID);
	exit(0);
}