#include<stdio.h>
#include<stdlib.h>
int main()
{
	int i,j;
	puts("Tabliczka mnożenia");
	for(i=0;i<=10;i++) printf("|%3d|",i);
	for(i=1;i<=10;i++)
	{
		printf("\n|%3d|",i);
		for(j=1;j<=10;j++)
			printf("|%3d|",i*j);
	}
	puts("");
	exit(0);
}