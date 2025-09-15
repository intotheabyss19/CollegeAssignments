/*
8. Enter two numbers from one end of the pipe and get the sum from the other end.
*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(void)
{
    int fd[2], a, b, sum;
    pid_t childpid;

    pipe(fd);

    if((childpid = fork()) == -1){
        perror("fork");
        exit(1);
    }

    if(childpid == 0){
        close(fd[0]);
        printf("Enter the values: ");
        scanf("%d%d", &a, &b);
        sum = a + b;
        write(fd[1], &sum, sizeof sum);
        exit(0);
    }else{
        close(fd[1]);
        read(fd[0], &sum, sizeof sum);
        printf("The total sum: %d\n", sum);
    }
    return 0;
}