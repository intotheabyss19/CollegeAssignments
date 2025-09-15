/*
19. Input a set of 10 numbers and display mean and standard deviation for this set of input.
*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <math.h>

void childP(int fd1[], int fd2[], float num[], int n)
{
    int i, sum = 0;
    float mean, std_dev, sq_sum = 0;

    close(fd1[0]); close(fd2[0]);

    for(i = 0; i < n; i++)
        sum += num[i];
    mean = sum / n;
    
    for(i = 0; i < n; i++)
        sq_sum += (num[i] - mean) * (num[i] - mean);
    std_dev = sqrt(sq_sum / n);

    write(fd1[1], &mean, sizeof mean);
    write(fd2[1], &std_dev, sizeof std_dev);
     
    close(fd1[1]); close(fd2[1]);
}

void parentP(int fd1[], int fd2[])
{
    float mean, std_dev;

    close(fd1[1]); close(fd2[1]);
    read(fd1[0], &mean, sizeof mean);
    read(fd2[0], &std_dev, sizeof std_dev);
    printf("Mean: %f\n", mean);
    printf("Standard Deviation: %f\n", std_dev);    

    close(fd1[0]); close(fd2[0]);
}

int main()
{
    int i, n = 10, fd1[2], fd2[2];
    float num[n];
    pid_t pid;

    pipe(fd1);
    pipe(fd2);

    if((pid = fork()) == -1)
    {
        perror("fork");
        exit(1);
    }
    else if(pid == 0)
    {
        printf("Enter 10 Numbers: ");
        for(i = 0; i < n; i++)
            scanf("%f", &num[i]);

        childP(fd1, fd2, num, n);
    }    
    else
        parentP(fd1, fd2);
    return 0;
}