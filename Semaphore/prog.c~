#include "semaphore.h"
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<unistd.h>

int main(int argc, char **argv)
{
	int i=0, loops=0, SemID=getSem(), ProgramID=0;
	if(argc==1)
	{
		puts("Nie podano ID");
		exit(1);
	}
	ProgramID=atoi(argv[1]);
	srand(time(NULL)-1);
	loops=(rand()%2+2);
	for(i=0;i<loops;++i)
	{
		printf("Przed sekcją     P%d: Value=%d, WaitP=%d, WaitZ=%d\n",ProgramID,Value(SemID),WaitP(SemID),WaitZ(SemID));
		PB(SemID);
		sleep(1+rand()%2);
		printf("W trakcie sekcji P%d: Value=%d, WaitP=%d, WaitZ=%d\n",ProgramID,Value(SemID),WaitP(SemID),WaitZ(SemID));
		sleep(1+rand()%2);
		VB(SemID);
		printf("Po sekcji        P%d: Value=%d, WaitP=%d, WaitZ=%d\n",ProgramID,Value(SemID),WaitP(SemID),WaitZ(SemID));
	}
	exit(0);
}