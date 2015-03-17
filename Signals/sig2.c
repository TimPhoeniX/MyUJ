#include<unistd.h>
#include<stdio.h>
#include<signal.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<sys/types.h>

int main()
{
	pid_t PID=0;
	switch (PID=fork())
		{
		case -1:
			perror("execl ERROR");
			exit(1);
			break;
        case 0:
			execl("./sig1.exe", "sig1.exe", (char*) NULL);
			break;
		default:
			sleep(1);
			break;
		}
	kill(PID,SIGINT);
    while (wait(NULL) != -1);
	exit(0);
}