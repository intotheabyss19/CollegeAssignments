/*
4. Write a program to declare an array of structures, where each element of the array is a structure
containing three variables, name, marks, and length, similar to Question no. 3 above. Take the names
and marks of a class of n students as input from the user (taking n also as input from the user), and then
store these n sets of data in the array of structures declared earlier, using the variable name to store
names and the variable marks to store marks. Calculate and store the length of each name in the
variable length. Display the following as the final output of your program: i) the longest name, ii) the
shortest name, iii) the highest marks along with the corresponing student’s name, iv) the lowest marks
along with the corresponding student’s name, v) the average marks of the whole class, and vi) the
number of students who have passed if pass marks is 40.
*/

#include <stdio.h>

struct student
{
    char name[64];
    float marks;
    int length;
};

int main()
{
    struct student stu[64];
    int n, i, j, space;
    int longN = 0, shortN = 0, highM = 0, lowM = 0;
    float avgMarks = 0;
    printf("Enter the number of students: ");
    scanf("%d", &n);
    getchar();

    for(i = 0; i < n; i++)
    {
        printf("\n\tStudent's name: ");
        fgets(stu[i].name, 48, stdin);
        printf("\tMarks: ");
        scanf("%f", &stu[i].marks);
        getchar();
        // Calculating length
        space = 0;
        for(j = 0, space = 0; stu[i].name[j] != '\0'; j++)
        {
            if(stu[i].name[j] == ' ')
                space++;
        }
        stu[i].length = j - space;
    }

    for(i = 0; i < n; i++)
    {
        if(stu[i].length > stu[longN].length)
            longN = i;
        if(stu[i].length < stu[shortN].length)
            shortN = i;
        if(stu[i].marks > stu[highM].marks)
            highM = i;
        if(stu[i].marks < stu[lowM].marks)
            lowM = i;
        avgMarks += stu[i].marks;
    }
    avgMarks /= n;

    printf("\nLongest Name: %s", stu[longN].name);
    printf("Shortest Name: %s", stu[shortN].name);
    printf("Highest Marks: %0.4f obtained by %s", stu[highM].marks, stu[highM].name);
    printf("lowest Marks: %0.4f obtained by %s", stu[lowM].marks, stu[lowM].name);
    printf("Average Marks of Whole Class: %.4f\n", avgMarks);

    printf("\nThe students who passed are: \n");
    for(i = 0; i < n; i++)
        if(stu[i].marks >= 40)
            printf("\t>%s", stu[i].name);

    return 0;
}

//Finished