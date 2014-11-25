#include<stdio.h>
#include<stdlib.h>
int main()
{
	char s[1024]; /*Should cover most sentences*/
	int i=0,count=1;
	puts("Enter a grammatically correct sentence");
	fgets(s,sizeof(s),stdin);
	while(s[i]!='\0') if(s[i++]==' ') ++count;
	fprintf(stdout,"This sentence contains %d words\n",count);
	exit(EXIT_SUCCESS);
} /* gcc word_count.c -o word_count -Wall -Wextra -pedantic -ansi */