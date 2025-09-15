/*
9.In the program written for Question no. 8 above, add statements to print the list of students who passed and
the list of students who failed and the corresponding count of students who passed and who failed, if the
pass marks is 40. (Make your output aesthetically attractive as advised by your instructors.)
*/

#include <stdio.h>

struct student
{
    char name[100];
    unsigned int roll;
    float marks;
    char stream[10];
}stu[100];

//functions for structure operations
void passfail(struct student s[], int);

//main function
int main()
{
    int i, n;
    //Taking the required student records as input
    printf("Enter the number of students: ");
    scanf("%d", &n);
    getchar();
    for(i = 0 ; i<n; i++)
    {
        printf("\t\nEntering data for student no. %d ==>\n", i+1);
        printf("Name of student: ");
        scanf("%s", &stu[i].name);
        printf("Roll number: ");
        scanf("%u", &stu[i].roll);
        printf("Marks Obtained: ");
        scanf("%f", &stu[i].marks);
        getchar();
        printf("Stream of the student: ");
        scanf("%s", &stu[i].stream);
    }

    //printing the data entered in a tabular format
    printf("\nSL. NO.\t|\tNAME\t|\tROLL NO.\t| MARKS OBTAINED  |  STREAM\t| STATEMENT");
    printf("\n");
    passfail(stu, n);
    return 0;
}


void passfail(struct student s[100], int n)
{
    int i=0;
    char *statement="fail";
    
    for (int i = 0; i < n; i++)
    {
        if(stu[i].marks>40)
            statement = "pass";
        printf("\n  %d\t\t%s\t\t%u\t\t  %.2f\t\t\t%s\t%s", i + 1, s[i].name, s[i].roll, s[i].marks, s[i].stream, statement);
        statement= "fail";
    }
    printf("\n");
}

//success