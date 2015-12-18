#include<stdio.h>
#include<stdlib.h>
float ctof(float c)
{
	return ((c*9/5)+32);
}
float ftoc(float f)
{
	return ((f-32)*5/9);
}
int main()
{
	float i;
	puts("This program will display temperatures in both Celsius and Fahrenheit");
	for(i=0;i<=100;i++)
		printf("%.0f degrees Celsius is %.2f degrees Fahrenheit and %.0f degrees Fahrenheit is %.2f degrees Celsius\n",i,ctof(i),i,ftoc(i));
	exit(0);
}