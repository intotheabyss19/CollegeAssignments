/*
2. Write a program to take the names and roll numbers of n students as input from the user (taking n also
as input from the user), and then ask the user to enter a roll number so that your program fetches the
corresponding name of the student. First create the database of the students, and then accept the query
from the user. The result of the query, i.e. the name of the student queried for, will be the final output of
the program. Do not use any structures.
*/

#include <stdio.h>

int main()
{
    char Names[50][50];
    int n, i, j, roll, rollList[50];

    printf("Enter the number of students: ");
    scanf("%d", &n);
    getchar();

    for(i = 0; i < n; i++)
    {
        printf("Name: ");
        fgets(Names[i], 48, stdin);
        printf("Roll Number: ");
        scanf("%d", &rollList[i]);
        getchar();
    }
    
    printf("Enter a roll number to be searched: ");
    scanf("%d", &roll);

    for(i = 0; i < n; i++)
    {
        if(roll == rollList[i])
        {
            printf("Found!, Name correspondig to roll number %d is %s", roll, Names[i]);
            return 0;
        }
    }
    printf("Not found!\n");
    return 0;
}

//Finished