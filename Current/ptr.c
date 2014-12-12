#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<stdarg.h>
#define TEST_VAL 8

void BetweenPointers(int *ptr1,int *ptr2,int value)
{
	int half=(ptr2-ptr1)/2,*temp=ptr1+half;
	*temp=value;
}
char* NotLetter(char* string)
{
	char* tmp=string;
	int i=0,length=strlen(string);
	while(i<length)
	{
		if( !(((*tmp>='A') && (*tmp<='Z')) || ((*tmp>='a') && (*tmp<='z'))) ) return tmp;
		else tmp++;
	}
	return tmp;
}
void CreateArrays(int **source,int ***ptrsarray)
{
	*source=malloc(10*sizeof(int));
	*ptrsarray=malloc(10*sizeof(int*));
}
void FillArrays(int *source,int **ptrsarray)
{
	int i=0;
	for(i=0;i<10;i++)
	{
		source[i]=rand()%100+1;
		ptrsarray[i]=&source[i];
	}
}
void ArrayOfPointersSort(int **ptrsarray)
{
	int i=0,j=0,*tmp=0;
	for(i=9;i>0;i--)
		for(j=0;j<i;j++)
			if(*ptrsarray[j]>*ptrsarray[j+1])
			{
				tmp=ptrsarray[j];
				ptrsarray[j]=ptrsarray[j+1];
				ptrsarray[j+1]=tmp;
			}
}
void Write(char* string,int n,...)
{
	char *current=string;
	int i=0,*number;
	va_list args;
	va_start(args,n);
	while(current[i]!='\0')
	{
		if(current[i]=='%' && current[i+1]=='d')
		{
			number=va_arg(args,int*);
			scanf("%d",number);
			i+=2;
		}
		else putchar(current[i++]);
	}
	va_end(args);
}
int main()
{
	int Tab[TEST_VAL]={1,2,3,4,5,6,7,8},*control=Tab,i=0;
	char *somechar=NULL;
	int *A, **B;
	int a=0,b=0;
	srand(time(NULL));
	for(i=0;i<TEST_VAL;i++) printf("%d, ",*(control++));
	BetweenPointers(Tab,&Tab[TEST_VAL-1],9);
	puts(""); control=Tab;
	for(i=0;i<TEST_VAL;i++) printf("%d, ",*(control++));
	somechar=NotLetter("Hallelujah!");
	printf("\nReceived \"%c\" (if received N then N stands for '\\0')\n",(*somechar!='\0'?*somechar:'N'));
	CreateArrays(&A,&B);
	FillArrays(A,B);
	for(i=0;i<10;i++) printf("%3d, %3d\n",A[i],*B[i]);
	ArrayOfPointersSort(B);
	puts("Post sorting");
	for(i=0;i<10;i++) printf("%3d, %3d\n",A[i],*B[i]);
	Write("Enter the length of a longer side of a rectangle %dEnter the length of a shorter side of a rectangle %d",2,&a,&b);
	printf("got %d and %d\n",a,b);
	exit(0);
}