#include<stdio.h>
#include<stdlib.h>
int main()
{
	int x,i,n=6;
	float a;
	puts("program obliczy średnią n liczb");
	srand(5);
	for(i=0;i<n;i++)
	{
		x=rand()%10+1;
		printf("%d. %d\n",i+1,x);
		a+=x;
	}
	printf("Średnia tych liczb wynosi %f\n",a/n);
	exit(0);
}