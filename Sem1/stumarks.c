//WACP that can store the individual marks of students in a structure and can call a function to calculate and show average marks.

#include <stdio.h>
#define NAMESIZE 100

//structure definition
struct stdata
{
    char name[NAMESIZE];
    float s1, s2, s3, s4, s5;
}s[40];


//prototype of the used functions
struct stdata stinput();
float mavg(struct stdata);


//main function
int main()
{
    int i, n;
    printf("\n");
    printf("Enter the number of students to be entered: ");
    scanf("%d", &n);
    printf("\n\n");
    //loop for entering the data of the students
    for (i=0; i<n; i++)
        s[i]=stinput();
    //loop for displaying the average of the given students
    printf("\tName\tAverage Marks\n");
    for(i=0; i<n; i++)
        printf("\t%s\t%f\n", s[i].name, mavg(s[i]));
    printf("\n");
    return 0;
}

//function to take student data as input
struct stdata stinput()
{
    struct stdata student;
    
    //taking input from the user
    printf("Enter the name of the Student: ");
    scanf("%s", &student.name);
    printf("\n");
    printf("Marks obtained in sub1: ");
    scanf("%f", &student.s1);
    printf("Marks obtained in sub2: ");
    scanf("%f", &student.s2);
    printf("Marks obtained in sub3: ");
    scanf("%f", &student.s3);
    printf("Marks obtained in sub4: ");
    scanf("%f", &student.s4);
    printf("Marks obtained in sub5: ");
    scanf("%f", &student.s5);

    //printing the entered data
    printf("\nYou entered: \n");
    printf("Name: %s\n", student.name);
    printf("rks obtained in subject 1: %f\n", student.s1);
    printf("Marks obtained in subject 2: %f\n", student.s2);
    printf("Marks obtained in subject 3: %f\n", student.s3);
    printf("Marks obtained in subject 4: %f\n", student.s4);
    printf("Marks obtained in subject 5: %f\n", student.s5);
    printf("\n");
    return student;
}

float mavg(struct stdata stu)
{
    //returning the average value
    float avg= (stu.s1+stu.s2+stu.s3+stu.s4+stu.s5)/5;
    return avg;
}