/*
3. Write a program to declare a structure, with the tag student, which contains three variables: i) name,
which can store a string, ii) marks, which can store a fraction, and iii) length, which can store an
integer. Take the values of name and marks from the user, and then calculate the length of name and
store it in length. Display all three values as the final output of your program.
*/

#include <stdio.h>

struct student
{
    char name[50];
    float marks;
    int length;
};

int main()
{
    struct student stu;
    int i = 0, space  = 1;
    printf("Enter your name: ");
    fgets(stu.name, 48, stdin);
    printf("Enter your marks: ");
    scanf("%f", &stu.marks);

    // Calculating length
    while(stu.name[i] != '\0')
    {
        i++;
        if(stu.name[i] == ' ')
            space++;
    }
    stu.length = i - space;

    // Displaying all three values
    printf("\n\tName: %s\tMarks: %.2f\n\tLength: %d\n", stu.name, stu.marks, stu.length);
}

//Finished