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
	int sourcedes=0,semid=0,shmid=0, state=0, *Written_Counter=NULL, buffsize=8;
	char *buffer=NULL, *buff_W=NULL ,*buffed_count=NULL, *completed;
	semid=getSem();
	shmid=accessShm(92);
	buffer=linkShm(shmid);
	Written_Counter=(int*)(buffer+80); /*licznik pilnuje, żeby konsument nie umieszczał powtarzających się fragmentów pliku*/
	completed=(char*)(buffer+88); /*Informacja dla konsumenta, kiedy może zakończyć działanie*/
	buff_W=(char*)(buffer+89); /*Wskazuje opdowiedni segment bufora*/
	buffed_count=(char*)(buffer+91); /*Liczba elementów w buforze*/
	if((sourcedes=open("source.txt",O_RDONLY,0644))==-1)
	{
		perror("open ERROR");
		exit(1);
	}
	while(1)
	{
		PB(semid);
		if(*completed)
		{
				VB(semid);
				break;
		}
		if((*buffed_count)<10)
		{
			if(lseek(sourcedes,(*Written_Counter)*buffsize,SEEK_SET)==-1)
			{
				perror("lseek ERROR");
				VB(semid);
				exit(1);
			}
			memset((buffer+(*buff_W)*buffsize),0,buffsize);
			if((state=read(sourcedes,buffer+(*buff_W)*buffsize,buffsize))==-1)
			{
				perror("read ERROR");
				VB(semid);
				exit(1);
			}
			if(state==0)
			{
				++(*completed);
				VB(semid);
				break;
			}
			else
			{
				++(*buff_W);
				if((*buff_W)>9) (*buff_W)=0;
				++(*buffed_count);
				++(*Written_Counter);
				VB(semid);
			}
		}
		else
		{
			VB(semid);
		}
	}
	unlinkShm(buffer);
	if(close(sourcedes)==-1)
	{
		perror("close ERROR");
		exit(1);
	}
	return 0;
}