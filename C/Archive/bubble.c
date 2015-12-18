#include<stdio.h>
#include<stdlib.h>
#include<time.h>
int MAX=0;
void print_array(int *t)
{
	int n;
	for(n=0;n<MAX;n++) printf("%2d, ",t[n]);
	puts("");
}
int main()
{
	int i=0,j=0,swap_made=0,temporary=0;
	int *array;
	puts("This program will bubble sort a random 1D array of numbers in ascending order.");
	srand(time(NULL));
	MAX=rand()%10+10;
	array=calloc(MAX,sizeof(int));
	for(i=0;i<MAX;i++) array[i]=rand()%100;
	print_array(array);
	puts("The numbers above will be sorted now");
/* Highest number gets sorted first
	for(i=MAX-1;i>0;i--)
	{
		swap_made=0;
		for(j=0;j<=i;j++)
		{	
			if(array[j]<array[j-1])
			{
				temporary=array[j];
				array[j]=array[j-1];
				array[j-1]=temporary;
				swap_made=1;
			}
		}
		if(!swap_made) break;
		print_array(array);
	}*/
/* Lowest number gets sorted first */
	for(i=0;i<MAX;i++)
	{
		swap_made=0;
		for(j=MAX;j>i;j--)
		{	
			if(array[j]<array[j-1])
			{
				temporary=array[j];
				array[j]=array[j-1];
				array[j-1]=temporary;
				swap_made=1;
			}
		}
		if(!swap_made) break;
		print_array(array);
	}
	exit(0);
}