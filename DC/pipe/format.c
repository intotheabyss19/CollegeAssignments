#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int childP(int fd[])
{
    
}

int parentP(int fd[])
{
    int xyz;
    close(fd[1]);
    read(fd[0], &xyz, sizeof xyz);
    printf("Mean: %d\n", xyz);

    close(fd[0]);
}

int main()
{
    int i, n, fd[2];
    pid_t pid;

    pipe(fd);

    if((pid = fork()) == -1){
        perror("fork");
        exit(1);
    }else if(pid == 0){

    }else{
        
    }
    return 0;
}