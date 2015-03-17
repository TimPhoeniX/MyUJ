#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>

int main()
{
    int status = 0, i = 0;
    printf("UID %d | GID %d | PID %d | PPID %d | PGID %d\n",
           getuid(), getgid(), getpid(), getppid(), getpgid(getpgrp()));
    sleep(1);
    for (i = 0; i < 3; i++)
    {
        switch (fork())
        {
        case -1:
            perror("execl ERROR");
            exit(1);
            break;
        case 0:
            execl("./ids.exe", "ids.exe", (char*) NULL);
            break;
        default:
            break;
        }
    }
    while (wait(&status) != -1);
    exit(0);
}