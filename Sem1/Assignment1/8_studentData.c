/*
8.Write a program to store a list of n records of students in an array of structures
(taking n as input from the user).
Each record of a student will contain the following attributes:
name of student, roll number of student, marks of student (which should be a real number),
academic stream of student.
After taking the records of n students, print all the records in a tabular format with appropriate column headings.
(Make your output aesthetically attractive as advised by your instructors).
*/

#include <stdio.h>

struct student
{
    char name[100];
    unsigned int roll;
    float marks;
    char stream[10];
} stu[100];

// functions for structure operations
void display(struct student s[], int);

// main function
int main()
{
    int i, n;
    // Taking the required student records as input
    printf("Enter the number of students: ");
    scanf("%d", &n);
    getchar();
    for (i = 0; i < n; i++)
    {
        printf("\t\nEntering data for student no. %d ==>\n", i);
        printf("Name of student: ");
        scanf("%s", &stu[i].name);
        printf("Roll number: ");
        scanf("%u", &stu[i].roll);
        printf("Marks Obtained: ");
        scanf("%f", &stu[i].marks);
        getchar();
        printf("Stream of the student: ");
        fgets(stu[i].stream, 5, stdin);
    }
    // printing the data entered in a tabular format
    printf("\nSL. NO.\t|\tNAME\t|\tROLL NO.\t|\tMARKS OBTAINED  |  STREAM");
    printf("\n");
    display(stu, n);
    return 0;
}

void display(struct student s[100], int n)
{
    for (int i = 0; i < n; i++)
        printf("\n  %d\t\t%s\t\t%u\t\t  %.2f\t\t\t%s", i + 1, s[i].name, s[i].roll, s[i].marks, s[i].stream);
    printf("\n");
}
// success