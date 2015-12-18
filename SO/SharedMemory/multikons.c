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
	int copydes=0, semid=0, shmid=0, *Written_Counter=NULL, *Read_Counter=NULL, buffsize=8;
	char *buffer=NULL, *buff_R=NULL, *buffed_count=NULL, *completed=NULL;
	if((copydes=open("copy.txt",O_WRONLY|O_CREAT,0644))==-1)
	{
		perror("open ERROR");
		exit(1);
	}
	semid=getSem();
	shmid=accessShm(92);
	buffer=linkShm(shmid);
	Written_Counter=(int*)(buffer+80);/*licznik pilnuje, żeby konsument nie umieszczał powtarzających się fragmentów pliku*/
	Read_Counter=(int*)(buffer+84);/*licznik elementów odczytanych z bufora.*/
	completed=(char*)(buffer+88);/*Informacja dla konsumenta, kiedy może zakończyć działanie*/
	buff_R=(char*)(buffer+90);/*Wskazuje opdowiedni segment bufora*/
	buffed_count=(char*)(buffer+91); /*Liczba elementów w buforze*/
	while(1)
	{
		PB(semid);
		if((*Read_Counter)<(*Written_Counter))
		{
			if((*buffed_count)>0)
			{
				if(lseek(copydes,(*Read_Counter)*buffsize,SEEK_SET)==-1)
				{
					perror("lseek ERROR");
					VB(semid);
					exit(1);
				}
				while((*(buffer+(*buff_R)*8+buffsize-1))==0) --buffsize;//Obcięcie bajtów 0.
				if(write(copydes,(buffer+8*(*buff_R)),buffsize)==-1)
				{
					perror("write ERROR");
					VB(semid);
					exit(1);
				}
				buffsize=8;
				++(*buff_R);
				if((*buff_R)>9) (*buff_R)=0;
				++(*Read_Counter);
				--(*buffed_count);
			}
		}
		VB(semid);
		if((*completed) && (*buffed_count==0)) break;
	}
	unlinkShm(buffer);
	if(close(copydes)==-1)
	{
		perror("close ERROR");
		exit(1);
	}
	return 0;
}