#include<stdio.h>
#include<stdlib.h>
int main()
{
 float c=0,f=0;
 int s=0;
 printf("Good Day\n");
 while(1)
 {s=0;
  printf("What would you like to do?\n1 - Convert Celsius to Fahrenheit.\n2 - Convert Fahrenheit to Celsius.\n3 - Quit.\nImproper Input will result in termiation of a program.\nOption: ");
  scanf("%d",&s);
  switch(s)
  {
   case 1:
    printf("Please, enter the temperature in Celsius: ");
    scanf("%f",&c); f=((c*9/5)+32);
    printf("%2.2f degrees Celsius is equal to %2.2f degrees Fahrenheit.\n",c,f);
    break;
   case 2:
    printf("Please, enter the temperature in Fahrenheit: ");
    scanf("%f",&f); c=((f-32)*5/9);
    printf("%2.2f degrees Fahrenheit is equal to %2.2f degrees Celsius.\n",f,c);
    break;
   case 3: exit(0);
   default: printf("Error, improper input.\n"); exit(0);
  } //End of switch 
  sleep(2);
 }//End of while
}//End of main