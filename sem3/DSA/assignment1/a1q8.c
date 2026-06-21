/*
8. Write a program to declare an array of structures where each instance of the structure stores the name of
an employee, the salary of the employee, and the age of the employee. Display as the final output of
your program the list of names of employees who are above 30 years of age and receive a salary greater
than Rs. 50,000.
*/

#include <stdio.h>

struct employee
{
    char name[50];
    double salary;
    unsigned short int age;
};

int main()
{
    struct employee emp[100];
    int n, i;
    printf("Enter the no of employees: ");
    scanf("%d", &n);
    for(i = 0; i < n; i++)
    {
        printf("Enter name: ");
        getchar();
        fgets(emp[i].name, 48, stdin);
        printf("Enter Salary: ");
        scanf("%lf", &emp[i].salary);
        printf("Enter age: ");
        scanf("%hu", &emp[i].age);
        printf("\n");
    }

    printf("Employees who are above 30 years of age and have salary greater than Rs. 50,000:\n");
    for(i = 0; i < n; i++)
        if(emp[i].age >= 30 && emp[i].salary >= 50000)
            printf("%s", emp[i].name);

    return 0;
}