/*
10. Write a program to declare a structure to represent a rectangle, and then find out the largest rectangle
from a set of rectangles. Declare an array of structures where every instance of the array is a structure
containing the length and breadth of a rectangle, where the length and breadth of n rectangles are taken
as input from the user and stored in this array of structures (n is also taken as user input). Display the
index number of the rectangle with the largest area as the final output of your program, i.e. if the mth
entered rectangle is the largest, m should be the final output.
*/

#include <stdio.h>

struct rectangle
{
    int length;
    int breadth;
};

int main()
{
    struct rectangle rect[50];
    int n, i, maxIndex = 0, areaMax = 0;
    printf("Enter number of rectangles: ");
    scanf("%d", &n);

    for(i = 0; i < n; i++)
    {
        printf("rectangle %d:\n", i+1);
        printf("length: "); 
        scanf("%d", &rect[i].length);
        printf("breadth: "); 
        scanf("%d", &rect[i].breadth);
        printf("\n");
    }

    // printing the index of biggest rectangle
    for(i = 0; i < n; i++)
    {
        if(rect[i].length * rect[i].breadth > areaMax)
        {
            maxIndex = i; 
            areaMax = rect[i].length * rect[i].breadth;
        }
    }
    printf("The largest rectangle is rectangle no. %d\n", maxIndex + 1);
    return 0;
}

// Finished