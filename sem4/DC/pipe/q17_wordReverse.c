/*
17.  Enter a word and display the word in reverse order.
*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>

int childP(int fd[])
{
    close(fd[0]);
    char str[100];
    printf("Enter a word: ");
    fgets(str, sizeof(str), stdin);
    str[strlen(str) - 1] = '\0';
    write(fd[1], str, strlen(str) + 1);
    close(fd[1]);
}

int parentP(int fd[])
{
    close(fd[1]);
    char str[100];
    read(fd[0], str, sizeof(str));
    printf("Word in reverse order: ");
    for(int i = strlen(str) - 1; i >= 0; i--)
        printf("%c", str[i]);
    printf("\n");
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