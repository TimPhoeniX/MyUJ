#include<stdlib.h>
#include<stdio.h>
#include<math.h>
int main()
{
 float a=0,b=0,c=0,d=0;
 printf("Podaj współczynniki a b c równania kwadratowego postaci ax^2+bx+c=0: ");
 scanf("%f %f %f",&a,&b,&c);
 if(a==0) {printf("To nie jest równanie kwadratowe\n"); exit(0);}
 d=((b*b)-(4*a*c));
 if(d<0) printf("To równanie kwadratowe nie posiada pierwiastów\n");
 else if(d==0) printf("Równanie posiada jeden pierwiastek podwójny x=%2.4f\n)",(-b)/(2*a));
      else printf("Równanie posiada dwa pierwiastki x1=%2.4f i x2=%2.4f\n",((-b-sqrt(d))/(2*a)),((-b+sqrt(d))/(2*a)));
 exit(0);
}