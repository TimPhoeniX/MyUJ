#include<stdio.h>
#include<stdlib.h>
int main()
{
	unsigned char i;
	printf("%d\n",sizeof(char));
	for(i=0;i<=127;i++)
		printf("%i = %c\n",i,i);
	exit(0);
}