/*
15.  Input numbers 1 – 9 in any order and display the corresponding cardinality e.g. 2 (Input), Second 
(output) 
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int childP(int fd[])
{
    int n;
    close(fd[0]);
    while(1) {
        printf("Enter a number (0 to exit): ");
        scanf("%d", &n);
        if(n < 0 || n > 9) {
            printf("Invalid input. Please enter a number between 0 and 9.\n");
            continue;
        }
        write(fd[1], &n, sizeof n);
        if(n == 0) 
            break;
        wait(NULL);
    }
    close(fd[1]);
}

int parentP(int fd[])
{
    int n;
    close(fd[1]);
    while(1) {
        read(fd[0], &n, sizeof n);
        if(n == 0) 
            break;
        printf("The corresponding cardinality is: ");
        switch(n)
        {
            case 1: printf("First");break;
            case 2: printf("Second");break;
            case 3: printf("Third");break;
            case 4: printf("Fourth");break;
            case 5: printf("Fifth");break;
            case 6: printf("Sixth");break;
            case 7: printf("Seventh");break;
            case 8: printf("Eighth");break;
            case 9: printf("Ninth");break;
            default: break;
        }
        printf("\n");
    }
    close(fd[0]);
}

int main(){
    int fd[2];
    pid_t pid;
    pipe(fd);
    if((pid = fork()) == -1){
        perror("fork");
        exit(1);
    }else if(pid == 0)
        childP(fd);
    else
        parentP(fd);

    return 0;
}