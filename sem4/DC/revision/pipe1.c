/* 
 * Write a pipe program in C to print the number pattern to form a triangle.
 * Take the input from the parent process as the number of lines in the pattern, 
 * and the child process should print the pattern. 
 * Once the pattern is successfully printed, 
 * the child should send back the sum of all the unique numbers to the parent
 */

#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main()
{
	int fd[2];
	pid_t pid;

	pipe(fd);

	pid = fork();

	if (pid > 0) {		// Parent Process
		int n, val;
		printf("Enter a number: ");
		scanf("%d", &n);
		write(fd[1], &n, sizeof(n));

		wait(&pid);
		read(fd[0], &val, sizeof(val));

		printf("The sum is: %d\n", val);
		close(fd[1]);
		close(fd[0]);
	}
	else if (pid == 0) {	// child process
		int a, i, j, sum = 0;
		read(fd[0], &a, sizeof(a));
		printf("The number is %d\n", a);

		for (i = 0; i < a; i++) {
			for (j = i; j < a; j++) {
				printf("%d ", j);
			}
			sum += i - 1;
			printf("\n");
		}
		sum += i;
		write(fd[1], &sum, sizeof(sum));
		close(fd[0]);
		close(fd[1]);
	}
	else {
		perror("Error in forking\n");
		return -1;
	}
	return 0;
}
