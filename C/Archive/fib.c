#include<stdio.h>
unsigned long int fib(int i)
{
	if(i==0) return 0;
	else if(i==1) return 1;
	else return (fib(i-1)+fib(i-2));
}
int main()
{
	int i;
	puts("First 20 numbers in Fibonacci series");
	for(i=0;i<20;i++) fprintf(stdout,"%lu, ",fib(i));
	fputs("\n",stdout);
	return 0;
} /*gcc fib.c -o fib -Wall -Wextra -pedantic -ansi*/