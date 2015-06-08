#include "semaphore.h"
#include<stdio.h>
#include<stdlib.h>

#if defined(__GNU_LIBRARY__) && !defined(_SEM_SEMUN_UNDEFINED)
#else
union semun
{
	int val;
	struct semid_ds *buf;
	unsigned short *array;
//	struct seminfo *__buf;
};
#endif

int createSem(void)
{
	key_t key;
	int semid;
	if((key=ftok(".",'X'))==-1)
	{
		perror("ftok ERROR");
		exit(1);
	}
	if((semid=semget(key,1,IPC_CREAT|IPC_EXCL|0666))==-1)
	{
		perror("semget ERROR");
		exit(1);
	}
	return semid;
}
int removeSem(int semid)
{
	if(semctl(semid,0,IPC_RMID)==-1)
	{
		perror("semctl ERROR");
		exit(1);
	}
	return 0;
}
int getSem(void)
{
	key_t key;
	int semid;
	if((key=ftok(".",'X'))==-1)
	{
		perror("ftok ERROR");
		exit(1);
	}
	if((semid=semget(key,1,0666))==-1)
	{
		perror("semget ERROR");
		exit(1);
	}
	return semid;
}
int initializeSem(int semid)
{
	union semun arg;
	arg.val=1;
	if(semctl(semid,0,SETVAL,arg)==-1)
	{
		perror("semctl ERROR");
		exit(1);
	}
	return 0;
}
int Value(int semid)
{
	int semval;
	if((semval=semctl(semid,0,GETVAL))==-1)
	{
		perror("semctl ERROR");
		exit(1);
	}
	return semval;
}
int WaitP(int semid)
{
	int waiting;
	if((waiting=semctl(semid,0,GETNCNT))==-1)
	{
		perror("semctl ERROR");
		exit(1);
	}
	return waiting;
}
int WaitZ(int semid)
{
	int waiting;
	if((waiting=semctl(semid,0,GETZCNT))==-1)
	{
		perror("semctl ERROR");
		exit(1);
	}
	return waiting;
}
int PB(int semid)
{
	struct sembuf buff={0,-1,0};
	if(semop(semid,&buff,1)==-1)
	{
		perror("semop ERROR");
		exit(1);
	}
	return 0;
}
int VB(int semid)
{
	struct sembuf buff={0,1,0};
	int semval=Value(semid);
	if(semval==1) return 0;
	if(semop(semid,&buff,1)==-1)
	{
		perror("semop ERROR");
		exit(1);
	}
	return 0;
}
int Z(int semid)
{
	struct sembuf buff={0,0,0};
	if(semop(semid,&buff,1)==-1)
	{
		perror("semop ERROR");
		exit(1);
	}
	return 0;
}