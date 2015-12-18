#ifndef _SEMAPHORE_H_
#define _SEMAPHORE_H_

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