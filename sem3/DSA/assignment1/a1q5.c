/*
5. Solve the same problem given in Question no. 2 above, but by using an array of structures where each
instance of the structure will contain the name and roll number of a student. As in Question no. 2, the
name of the student queried for will be the final output of the program.
*/
/*
2. Write a program to take the names and roll numbers of n students as input from the user (taking n also
as input from the user), and then ask the user to enter a roll number so that your program fetches the
corresponding name of the student. First create the database of the students, and then accept the query
from the user. The result of the query, i.e. the name of the student queried for, will be the final output of
the program. Do not use any structures.
*/

#include <stdio.h>

struct student
{
    char name[50];
    int roll;
};

int main()
{
    struct student stu[50];
    
    int n, roll, i;

    printf("Enter number of names: ");
    scanf("%d", &n);

    for(i = 0; i < n; i++)
    {
        printf("Name: ");
        getchar();
        fgets(stu[i].name, 48, stdin);
        printf("Roll No: ");
        scanf("%d", &stu[i].roll);
    }

    printf("Enter a roll number to be searched: ");
    scanf("%d", &roll);

    for(i = 0; i < n; i++)
    {
        if(roll == stu[i].roll)
        {
            printf("Found!, Name correspondig to roll number %d is %s", roll, stu[i].name);
            return 0;
        }
    }
    printf("Not found!\n");
    return 0;
}

//Finished