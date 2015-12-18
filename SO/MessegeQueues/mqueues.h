#ifndef _MQUEUES_H_
#define _MQUEUES_H_

int createMessegeQueue(void);
int getMessageQueue(void);
int removeMessageQueue(int msgid);
unsigned short getQueueLength(int msgid);
struct msqid_ds getMessageQueueStats(int msgid);
void sendMessage(int msgid, void *message, size_t size);
int receiveMessageNB(int msgid, void *message, size_t size, long msgtype)
void receiveMessage(int msgid, void *message, size_t size, long msgtype);
int checkQueueExistance();