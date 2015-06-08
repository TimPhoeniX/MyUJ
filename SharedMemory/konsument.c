#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>
#include "semaphore.h"
#include "sharedmem.h"

int main(void)
{
	int copydes=0,semid=0,shmid=0,buffcount=0,loops=0, *counter=NULL, buffsize=8;
	char *buffer=NULL, *completed=NULL;
	if((copydes=open("copy.txt",O_WRONLY|O_CREAT,0644))==-1)
	{
		perror("open ERROR");
		exit(1);
	}
	semid=getSem();
	shmid=accessShm(85);
	buffer=(char*)linkShm(shmid);
	counter=(int*)(buffer+80);
	completed=(char*)(buffer+84);
//	printf("Kons - Semid=%d, Shmid=%d, Buffer=%p\n",semid,shmid,buffer);
	while(1)
	{
		PB(semid);
		if(loops<(*counter))
		{
			while((*(buffer+buffcount*8+buffsize-1))==0) --buffsize;
			if(write(copydes,buffer+buffcount*8,buffsize)==-1)
			{
				perror("write ERROR");
				exit(1);
			}
			++buffcount;
			if(buffcount>9) buffcount=0;
			++loops;
		}
		VB(semid);
		if(loops==*counter && *completed) break;
	}
	unlinkShm(buffer);
	if(close(copydes)==-1)
	{
		perror("close ERROR");
		exit(1);
	}
	exit(0);
}