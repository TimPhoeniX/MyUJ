#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<unistd.h>
#include "mqueues.c"

struct MESSAGE
{
	long receiver;
	long sender;
	char message[64];
};

int main(void)
{
	int msgid=createMessageQueue(), msglen=0, i=0, idle_count=5;
	struct MESSAGE msg={0,0,{0}};
	while(1)
	{
		if(getQueueLength(msgid))
		{
			if(receiveMessageNB(msgid,&msg,sizeof(msg),1))
			{
				idle_count=5;
				printf("Received Message: %s\n",msg.message);
				msglen=strlen(msg.message);
				for(i=0;i<msglen;++i)
				{
					msg.message[i]=toupper(msg.message[i]);
				}
				msg.receiver=msg.sender;
				printf("Returning Message: %s\n",msg.message);
				sendMessage(msgid,&msg,sizeof(msg));
			}
		}
		else
		{
			if(!(idle_count--)) break;
			sleep(1);
		}
	}
	removeMessageQueue(msgid);
	return 0;
}