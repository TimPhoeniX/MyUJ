#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#include<stdio.h>
#include<stdlib.h>
#include<errno.h>

int createMessageQueue(void)
{
	key_t key;
	int msgid;
	if((key=ftok(".",'X'))==-1)
	{
		perror("ftok ERROR");
		exit(1);
	}
	if((msgid=msgget(key,IPC_CREAT|IPC_EXCL|0666))==-1)
	{
		perror("msgget ERROR");
		exit(1);
	}
	return msgid;
}
int getMessageQueue(void)
{
	key_t key;
	int msgid;
	if((key=ftok(".",'X'))==-1)
	{
		perror("ftok ERROR");
		exit(1);
	}
	if((msgid=msgget(key,0666))==-1)
	{
		perror("msgget ERROR");
		exit(1);
	}
	return msgid;
}
int removeMessageQueue(int msgid)
{
	if(msgctl(msgid,IPC_RMID,(struct msqid_ds*)0)==-1)
	{
		perror("msgctl ERROR");
		exit(1);
	}
	return 0;
}
struct msqid_ds getMessageQueueStats(int msgid)
{
	struct msqid_ds buff;
	if(msgctl(msgid,IPC_STAT,&buff)==-1)
	{
		perror("msgctl ERROR");
		exit(1);
	}
	return buff;
}
unsigned short getQueueLength(int msgid)
{
	struct msqid_ds buff=getMessageQueueStats(msgid);
	return buff.msg_qnum;
}
void sendMessage(int msgid, void *message, size_t size)
{
	if(msgsnd(msgid,message,size,0)==-1)
	{
		perror("msgsnd ERROR");
		exit(1);
	}
}
void receiveMessage(int msgid, void *message, size_t size, long msgtype)
{
	if(msgrcv(msgid,message,size,msgtype,0)==-1)
	{
		perror("msgsnd ERROR");
		exit(1);
	}
}
int receiveMessageNB(int msgid, void *message, size_t size, long msgtype)
{
	if(msgrcv(msgid,message,size,msgtype,IPC_NOWAIT)==-1)
	{
		if(errno==ENOMSG)
			return 0;
		perror("msgsnd ERROR");
		exit(1);
	}
	return 1;
}
int checkQueueExistance()
{
	key_t key;
	if((key=ftok(".",'X'))==-1)
	{
		perror("ftok ERROR");
		exit(1);
	}
	if(msgget(key,0)==-1)
	{
		if(errno==ENOENT)
			return 0;
		else
		{
			perror("msgget ERROR");
			exit(1);
		}
	}
	return 1;
}