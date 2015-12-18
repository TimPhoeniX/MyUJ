#include<stdio.h>
#include<stdlib.h>
#include<string.h>
char s[10];
char get_control()
{
	fgets(s,sizeof(s),stdin);
	if(!strcmp(s,"0\n")) exit(0);
	   else return s[0];
}
float get_number()
{
	float number;
	while(!scanf("%f",&number))
	{
		puts("It's not a number");
		fgets(s,sizeof(s),stdin);
	}
	getchar();
	return number;
}
int main()
{
	float a=0,total=0;
	char control;
	while(1)
	{
		printf("Enter the sign of the operation you want to perform on your numbers\n(+|-|*|/) or 0 to exit the program\nThe current number in the memory is %f\n",total);
		control=get_control();
		switch(control)
		{
			case '+':
				printf("Enter the number you want to add to %f\n",total);
				a=get_number();
				printf("%f+%f=",total,a);printf("%f\n",total+=a);
				break;
			case '-':
				printf("Enter the number you want to substract from %f\n",total);
				a=get_number();
				printf("%f-%f=",total,a);printf("%f\n",total-=a);
				break;
			case '*':
				printf("Enter the number you want %f to be multiplied by\n",total);
				a=get_number();
				printf("%f*%f=",total,a);printf("%f\n",total*=a);
				break;
			case '/':
				printf("Enter the number you want %f to be divided by\n",total);
				a=get_number();
				if(a==0)
				{
					puts("I'm afraid I can't do that");
					break;
				}
				printf("%f/%f=",total,a);printf("%f\n",total/=a);
				break;
			default:
				puts("I'm afraid I can't do that");
				break;
		}
	}
	exit(0);
}
	