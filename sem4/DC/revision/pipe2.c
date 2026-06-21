/*
 * Write a pipe program in C to print the number pattern to form a triangle.
 * Take the input from the parent process as the number of lines in the pattern,
 * and the child process should print the pattern. Once the pattern is successfully printed,
 * the child should return the largest prime number used in the pattern to the parent.
*/

#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int is_prime(int x) { 
	if (x < 2) return 0;
	for (int i = 2; i * i <= x; i++)  
		if (x % i == 0) return 0;
	return 1; 
}

int main() {
	pid_t pid;
	int fd[2];

	pipe(fd);
	pid = fork();

	if (pid > 0) {		// parent process
		int n, lp;
		printf("Enter the number of lines: ");
		scanf("%d", &n);
		write(fd[1], &n, sizeof n);

		wait(&pid);
		read(fd[0], &lp, sizeof lp);

		printf("The largest prime is: %d\n", lp);
		close(fd[1]);
		close(fd[0]);
	}
	else if (pid == 0) {	// child process
		int a, i, j, sum = 0, lprime = 0;
		read(fd[0], &a, sizeof(a));
		printf("The number is %d\n", a);

		for (i = 0; i < a; i++) {
			for (j = i; j < a; j++) {
				if (is_prime(j) && j > lprime) lprime = j;
				printf("%d ", j);
			}
			sum += i - 1;
			printf("\n");
		}
		write(fd[1], &lprime, sizeof(int));
		close(fd[0]);
		close(fd[1]);
	}
	else {
		perror("Error in forking\n");
		return -1;
	}
	return 0;
}
