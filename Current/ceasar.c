#include<stdio.h>
#include<ctype.h>
int main()
{
	char s[1024];
	int i;
	puts("Classic Ceaser Cipher(by 3) that omits interpunction,numbers and returns UPPERCASE string.");
	puts("1 for leftshit, 2 for rightshift, else quit");
	scanf("%d",&i);
	getchar();
	switch(i)
	{
		case 1:
			puts("Enter a string you want to leftshit");
			fgets(s,sizeof(s),stdin);
			i=0;
			while(s[i]!='\0')
			{
				s[i]=toupper(s[i]);
				if(s[i]>'A' && s[i]<'Z') s[i]=(s[i]-3<'A')?s[i]+23:s[i]-3;
				i++;
			}
			puts(s);
			break;
		case 2:
			puts("Enter a string you want to rightshit");
			fgets(s,sizeof(s),stdin);
			i=0;
			while(s[i]!='\0')
			{
				if(s[i]>'A' && s[i]<'Z') s[i]=(s[i]+3>'Z')?s[i]-23:s[i]+3;
				i++;
			}
			puts(s);
			break;
	}
	return 0;
} /*gcc ceasar.c -o ceasar -Wall -Wextra -pedantic -ansi*/