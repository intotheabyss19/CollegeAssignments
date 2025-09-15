/*
6. Write a program to store in two separate array the prime numbers and the non-prime numbers of a given
array of integers with a function called separate. Define separate as follows:
separate(list, primes, nonprimes) will store in primes the prime numbers from list and will store in
nonprimes the non-prime numbers from list. Take an array called list as input from the user, and print the
two arrays containing the prime numbers and the non-prime numbers of list in two separate lines as the
final output of your program.
*/

#include <stdio.h>

void separate(int list[], int primes[], int nonprimes[], int *size, int *p, int *np);
int primecheck(int); // function to check whether a number is prime or not

void printall()
{
    for (int i = 0; i < 1000; i++)
        if (primecheck(i))
            printf("%d ", i);
}

int main()
{
    int i, n, p = 0, np = 0, arr[100], primes[100], nonprimes[100];

    // basic loop to take the array input from the user
    printf("Enter the number of elements: ");
    scanf("%d", &n);
    for (i = 0; i < n; i++)
    {
        printf("Element no. %d: ", i + 1);
        scanf("%d", &arr[i]);
    }

    // calling the separate function
    separate(arr, primes, nonprimes, &n, &p, &np);

    // printing the primes
    printf("Primes: ");
    for (i = 0; i < p; i++)
        printf("%d ", primes[i]);

    // printing the nonprimes
    printf("\nNonPrimes: ");
    for (i = 0; i < np; i++)
        printf("%d ", nonprimes[i]);

    printf("\n");
    // main function ends here
    return 0;
}

void separate(int list[], int primes[], int nonprimes[], int *s, int *p, int *np)
{
    int i = 0;
    for (i; i < *s; i++)
    {
        if (primecheck(list[i]))
        {
            primes[*p] = list[i];
            (*p)++;
        }
        else
        {
            nonprimes[*np] = list[i];
            (*np)++;
        }
    }
}

int primecheck(int n)
{
    if (n == 1 || n == 0)
        return 0;
    for (int i = 2; i <= n / 2; i++)
        if (n % i == 0)
            return 0;
    return 1;
}

//success