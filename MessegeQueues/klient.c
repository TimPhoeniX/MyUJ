#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include "mqueues.c"

struct MESSAGE
{
	long receiver;
	long sender;
	char message[64];
};

int main(int argc, char** argv)
{
	int msgid=0;
	struct MESSAGE msg={1,getpid(),{0}};
	if(argc<2)
	{
		puts("No string received");
		exit(1);
	}
	strncpy((char*)&msg.message,argv[1],63);
	while(!checkQueueExistance());
	msgid=getMessageQueue();
	sendMessage(msgid,&msg,sizeof(msg));
	receiveMessage(msgid,&msg,sizeof(msg),getpid());
	puts(msg.message);
	return 0;
}