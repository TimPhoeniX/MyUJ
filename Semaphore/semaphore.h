#ifndef _SEMAPHORE_H_
#define _SEMAPHORE_H_

#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/sem.h>

int createSem(void);
int initializeSem(int semid);
int removeSem(int semid);
int getSem(void);
int Value(int semid);
int WaitP(int semid);
int WaitZ(int semid);
int PB(int semid);
int VB(int semid);
int Z(int semid);

#endif