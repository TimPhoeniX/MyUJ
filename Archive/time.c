#include<stdio.h>
#include<stdlib.h>
int main()
{unsigned int time[1][3];
puts("Please, enter two different times in hh:mm:ss format");
scanf("%d:%d:%d",&time[0][0],&time[0][1],&time[0][2]);
scanf("%d:%d:%d",&time[1][0],&time[1][1],&time[1][2]);
if(time[0][0]>24 || time[1][0]>24){printf("Wrong input, Shutting down\n"); exit(0);}
else if(time[0][1]>59 || time[1][1]>59){printf("Wrong input, Shutting down\n"); exit(0);}
else if(time[0][2]>59 || time[1][2]>59){printf("Wrong input, Shutting down\n"); exit(0);}
if(time[0][0]==time[1][0])
  if(time[0][1]==time[1][1])
    if(time[0][2]==time[1][2]) printf("You gave entered the same time twice\n");
    else if(time[0][2]<time[1][2]) printf("%02d:%02d:%02d is earlier than %02d:%02d:%02d\n",time[0][0],time[0][1],time[0][2],time[1][0],time[1][1],time[1][2]);
         else printf("%02d:%02d:%02d is later than %02d:%02d:%02d\n",time[0][0],time[0][1],time[0][2],time[1][0],time[1][1],time[1][2]);
  else if(time[0][1]<time[1][1]) printf("%02d:%02d:%02d is earlier than %02d:%02d:%02d\n",time[0][0],time[0][1],time[0][2],time[1][0],time[1][1],time[1][2]);
       else printf("%02d:%02d:%02d is later than %02d:%02d:%02d\n",time[0][0],time[0][1],time[0][2],time[1][0],time[1][1],time[1][2]);
else if(time[0][0]<time[1][0]) printf("%02d:%02d:%02d is earlier than %02d:%02d:%02d\n",time[0][0],time[0][1],time[0][2],time[1][0],time[1][1],time[1][2]);
       else printf("%02d:%02d:%02d is later than %02d:%02d:%02d\n",time[0][0],time[0][1],time[0][2],time[1][0],time[1][1],time[1][2]);
exit(0);
}