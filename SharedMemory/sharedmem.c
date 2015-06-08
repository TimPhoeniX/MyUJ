#include "sharedmem.h"
#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/shm.h>

int createShm(int size)
{
	key_t key;
	int shmid;
	if((key=ftok(".",'Y'))==-1)
	{
		perror("ftok ERROR");
		exit(1);
	}
	if((shmid=shmget(key,size,IPC_CREAT|IPC_EXCL|0666))==-1)
	{
		perror("shmget ERROR");
		exit(1);
	}
	return shmid;
}
int removeShm(int shmid)
{
	if(shmctl(shmid,IPC_RMID,(struct shmid_ds*)0)==-1)
	{
		perror("shmctl ERROR");
		exit(1);
	}
	return 0;
}
int accessShm(int size)
{
	key_t key;
	int shmid;
	if((key=ftok(".",'Y'))==-1)
	{
		perror("ftok ERROR");
		exit(1);
	}
	if((shmid=shmget(key,size,0666))==-1)
	{
		perror("shmget ERROR");
		exit(1);
	}
	return shmid;
}
void* linkShm(int shmid)
{
	void* shmaddr=shmat(shmid,NULL,0);
	if(shmaddr==(void*)-1)
	{
		perror("shmadrr ERROR");
		exit(1);
	}
	return shmaddr;
}
int unlinkShm(void* shmaddr)
{
	if(shmdt(shmaddr)==-1)
	{
		perror("shmdt ERROR");
		exit(1);
	}
	return 0;
}
struct shmid_ds getShmStats(int shmid)
{
	struct shmid_ds Stats;
	if(shmctl(shmid,IPC_STAT,&Stats)==-1)
	{
		perror("shmctl ERROR");
		exit(1);
	}
	return Stats;
}
int getShmAttachments(int shmid)
{
	return getShmStats(shmid).shm_nattch;
}