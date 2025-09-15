/*
16.  Input temperature in ºC and display the temperature in ºF. 
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int childP(int fd[])
{
    close(fd[0]);
    float celsius;
    printf("Enter temperature in Celsius: ");
    scanf("%f", &celsius);
    write(fd[1], &celsius, sizeof celsius);
    close(fd[1]);
}

int parentP(int fd[])
{
    float celsius;
    close(fd[1]);
    read(fd[0], &celsius, sizeof celsius);
    printf("%.2f°C is equal to %.2f°F\n", celsius, (celsius *9/5.0) + 32);
    close(fd[0]);
}

int main()
{
    int fd[2];
    pid_t pid;

    pipe(fd);

    if((pid = fork()) == -1){
        perror("fork");
        exit(1);
    }else if(pid == 0){
        childP(fd);
    }else{
        parentP(fd);
        wait(NULL);
    }
    return 0;
}