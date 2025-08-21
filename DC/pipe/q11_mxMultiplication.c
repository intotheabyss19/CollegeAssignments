/*
11.  Input 8 numbers and display/output the result by 2X2 matrix manipulation.
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int child(int fd[])
{
    close(fd[0]);

    int m1[2][2], m2[2][2];
    printf("Enter 4 numbers for matrix 1: ");
    for(int i = 0; i < 2; i++)
        for(int j = 0; j < 2; j++)
            scanf("%d", &m1[i][j]);

    printf("\nEnter 4 numbers for matrix 2: ");
    for(int i = 0; i < 2; i++)
        for(int j = 0; j < 2; j++)
            scanf("%d", &m2[i][j]);

    write(fd[1], &m1, sizeof m1);
    write(fd[1], &m2, sizeof m2);
    exit(0);
}

int parent(int fd[])
{
    int m1[2][2], m2[2][2], temp, i , j, k ;
    close(fd[1]);
    wait(NULL);
    printf("\nThe product matrix is: \n");
    read(fd[0], m1, sizeof m1);
    read(fd[0], m2, sizeof m2);

    for( i = 0; i < 2; i++){
        for( j = 0; j < 2; j++){
            temp = 0;
            for( k = 0; k < 2; k++)
                temp += m1[i][k] * m2[k][j];
            printf("%d ", temp);
        }
        printf("\n");
    }
    
    exit(0);    
}

int main()
{
    int i, n, fd[2];
    pid_t pid;

    pipe(fd);

    if((pid = fork()) == -1){
        perror("fork error");
        exit(1);
    }

    if(pid == 0)
        child(fd);
    else
        parent(fd);
    return 0;
}