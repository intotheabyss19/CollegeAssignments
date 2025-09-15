/*
10.  Collect the Ethernet address in hexadecimal and generate the 48 bit pattern of the same. 
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int childP(int fd[]) {
    close(fd[0]);
    int hexAddress;
    printf("Enter the Ethernet Address: ");
    scanf("%x", &hexAddress);
    printf("The Entered number is: %x\n", hexAddress);
    write(fd[1], &hexAddress, sizeof hexAddress);
    close(fd[1]);
}

int parentP(int fd[]) {
    int hexAddress;
    close(fd[1]);
    read(fd[0], &hexAddress, sizeof hexAddress);
    printf("The Decimal number is: %d\n", hexAddress);
    printf("The Binary representation is: %b\n", hexAddress);
    close(fd[0]);
}

int main() {
    int i, n, fd[2];
    pid_t pid;

    pipe(fd);

    if((pid = fork()) == -1){
        perror("fork");
        exit(1);
    }else if(pid == 0){
        childP(fd);
    }else{
        parentP(fd);
    }
    return 0;
}