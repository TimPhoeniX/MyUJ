#include "semaphore.h"
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>

int main(int argc, char **argv)
{
	int SemID=0, i=0, nextProgramID=0;
	char programID[64];
	
	if(argc==1)
	{
		puts("Nie podano liczby programów");
		exit(1);
	}
	
	SemID=createSem();
	initializeSem(SemID);
	printf("SemID=%d\n",SemID);
	
	for (i = 0; i < atoi(argv[1]); i++)
	{
		snprintf(programID,64,"%d",nextProgramID++);
		switch (fork())
		{
		case -1:
			perror("fork ERROR");
			exit(1);
			break;
		case 0:
			execl("./prog.exe","prog.exe",programID,(char*) NULL);
			perror("execl ERROR");
			_exit(2);
			break;
		default:
			break;
		}
	}
	while (wait(NULL) != -1);
	removeSem(SemID);
	exit(0);
}