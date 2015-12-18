#ifndef _SHAREDMEM_H_
#define _SHAREDMEM_H_

int createShm(int size);
void* linkShm(int shmid);
int unlinkShm(void* shmaddr);
int removeShm(int shmid);
int accessShm(int size);
int getShmAttachments(int shmid);
struct shmid_ds getShmStats(int shmid);

#endif