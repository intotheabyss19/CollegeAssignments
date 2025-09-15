/*
9. Input two numbers, through the child process and find their product and quotient in the parent 
process. If there is any error during the processing, display the error.
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int child(int fd[])
{
    int a, b, prod;
    float quot;
    close(fd[0]);
    printf("Enter the numbers: ");
    scanf("%d%d", &a, &b);
    prod = a * b;
    quot = (float)a / b;

    write(fd[1], &prod, sizeof prod);
    write(fd[1], &quot, sizeof quot);
    exit(0);
}

int parent(int fd[])
{
    int prod;
    float quot;
    close(fd[1]);
    read(fd[0], &prod, sizeof prod);
    read(fd[0], &quot, sizeof quot);
    printf("Product: %d\n", prod);
    printf("Quotient: %f\n", quot);
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