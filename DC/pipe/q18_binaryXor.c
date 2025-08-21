/*
18. Enter a number, convert it into binary (8 bits), XOR it with 10101011 and display the number in decimal.
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define XORval 0B10101011

int childP(int fd[], int dec)
{
    close(fd[0]);
    int result, bin = dec;
    printf("Binary representation of %d is: %B\n", dec, bin);
    result = bin ^ XORval;
    write(fd[1], &result, sizeof(result));
    close(fd[1]);
}

int parentP(int fd[])
{
    close(fd[1]);

    int result;
    read(fd[0], &result, sizeof result);
    printf("After manipulation: %d\n", result);

    close(fd[0]);
}

int main()
{
    int n, fd[2];
    pid_t pid;
    pipe(fd);
    if((pid = fork()) == -1){
        perror("fork");
        exit(1);
    }else if(pid == 0){
        printf("Enter a number: ");
        scanf("%d", &n);
        childP(fd, n);
    }else
        parentP(fd);
    return 0;
}