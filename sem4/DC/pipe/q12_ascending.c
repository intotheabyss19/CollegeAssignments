/*
12.  Enter/Input 10 numbers and display the numbers in ascending order.
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int child(int fd[])
{
    close(fd[0]);
    int nums[10];
    printf("Enter 10 numbers: ");
    for(int i = 0; i < 10; i++)
        scanf("%d", &nums[i]);

    write(fd[1], &nums, sizeof nums);
    exit(0);
}

int parent(int fd[])
{
    int nums[10], i, j, key;
    close(fd[1]);
    read(fd[0], nums, sizeof nums);
    printf("\nThe list in ascending order is: \n");

    for (i = 1; i < 10; i++) {
        key = nums[i];
        j = i - 1;

        while (j >= 0 && nums[j] > key) {
            nums[j + 1] = nums[j];
            j = j - 1;
        }
        nums[j + 1] = key;
    }
    for(int i = 0; i < 10; i++)
        printf("%d ", nums[i]);

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