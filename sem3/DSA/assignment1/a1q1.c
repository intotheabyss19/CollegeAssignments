/*
1. Write a program to store a set of names of students in an array and then find out the length of each name.
Take the number of students and the names of the students as inupt from the user.
After taking all the inputs, print the length values as the final output of your program.
*/
#include <stdio.h>
int nameLength(char name[]);

int main()
{
    int numStudents, i;
    char name[100][100];

    printf("Enter the number of students : ");
    scanf("%d", &numStudents);
    getchar();
    printf("Enter the names : \n");

    // Taking input
    for(i = 0; i < numStudents; i++)
    {
        printf("\t>");  
        fgets(name[i], 98, stdin);
    }

    // Printing the length values
    printf("\nThe lengths are: \n");
    for(i = 0; i < numStudents; i++)
        printf("\t>%s : %d \n", name[i], nameLength(name[i]));
}

int nameLength(char Name[])
{
    int i = 0, count = 0;
    while(Name[i] != '\0')
    {
        if(Name[i] == ' ')
            count--;
        i++;
        count++;
    }
    Name[i-1] = '\0';
    count--;
    return count;
}

//Finished