
#include <stdio.h>

int q1()
{
/*      Using Conditional Statement
1.	Write a C program to accept a coordinate point in a XY coordinate system and determine in which quadrant the coordinate point lies.
Test Data: 7 9 
Expected Output:
The coordinate point (7,9) lies in the First quadrant.
*/
    int x, y;

    // Input the coordinates
    printf("Enter the x-coordinate: ");
    scanf("%d", &x);
    printf("Enter the y-coordinate: ");
    scanf("%d", &y);

    //Conditional Statements
    if(x==0 && y==0)
    {
        printf("The coordinate point (%d,%d) is at the origin.\n", x, y);
    }
    else if(x==0)
    {
        printf("The coordinate point (%d,%d) is on the y-axis.\n", x, y);
    }
    else if(y==0)
    {
        printf("The coordinate point (%d,%d) is on the x-axis.\n", x, y);
    }

    else if (x > 0)
    {
        if (y>0)
        {
            printf("The coordinate point (%d,%d) lies in the First quadrant.\n", x, y);
        }
        else
        {
            printf("The coordinate point (%d,%d) lies in the Second quadrant.\n", x, y);
        }
    }

    else
    {
        if (y>0)
        {
            printf("The coordinate point (%d,%d) lies in the Third quadrant.\n", x, y);
        }
        else
            printf("The coordinate point (%d,%d) lies in the Fourth quadrant.\n", x, y);
    }
    return 0;
}

int q2()
{   
/*2.	Write a C program to find the eligibility of admission for a professional course based on the following criteria:
Eligibility Criteria: Marks in Maths >=65 and Marks in Phy >=55 and Marks in Chem>=50 and Total in all three subjects >=190 or Total in Maths and Physics >=140
Test Data: Input the marks obtained in Physics :65 Input the marks obtained in Chemistry :51 Input the marks obtained in Mathematics :72 Total marks of Maths, Physics and Chemistry: 188 Total marks of Maths and Physics: 137 The candidate is not eligible.
Expected Output:
The candidate is not eligible for admission.
*/

    float m,p,c,mpc,mp;
    //input the marks
    printf("Enter the marks obtained in Physics, Chemistry, Mathematics:\n");
    scanf("%f%f%f",&p,&c,&m);
    mp=m+p;
    mpc=mp+c;
    if (m>65 && p>55 && c>50 && mpc>190 && mp>140)
    {
        printf("The candidate is eligible for the admission.");
    }
    else
    {
        printf("The candidate is not eligible for the admission.\n");
    }
    return 0;
}

int q3()
{
/*
3.	Write a C program to read roll no, name and marks of three subjects and calculate the total, percentage and division. 
Test Data: 
Input the Roll Number of the student :784 
Input the Name of the Student: James 
Input the marks of Physics, Chemistry and Computer Application: 70 80 90
Expected Output:
Roll No: 784 
Name of Student: James 
Marks in Physics: 70 
Marks in Chemistry: 80 
Marks in Computer Application: 90 
Total Marks = 240 
Percentage = 80.00 
Division = First
*/
    int roll, division;
    float p,c,ca, total, percentage;
    char name[32];
    printf("Roll No: ");
    scanf("%d",&roll);
    printf("Name of the Student: ");
    scanf("%s", &name);
    printf("Marks in Physics: ");
    scanf("%f", &p);
    printf("Marks in Chemistry: ");
    scanf("%f", &c);
    printf("Marks in Computer Application: ");
    scanf("%f", &ca);
    //Requried Operations
    total= p+c+ca;
    percentage= total/3;
    // Output of the program
    printf("Total Marks = %f\n", total);
    printf("Percentage = %f\n", percentage);
    if (percentage>=80)
    {
        printf("Division = First\n");
    }
    else if (percentage>=60)
    {
        printf("Division = Second\n");
    }
    else if (percentage>=33)
    {
        printf("Division = Third\n");
    }
    else
    {
        printf("Failed\n");
    }
    return 0;
}

int q4()
{
/*4.	Write a C program to check whether a character is an alphabet, digit or special character. 
Test Data: @
Expected Output:
This is a special character.
*/
{
    char c;
    printf("Enter a character: ");
    scanf("%c", &c);
    if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
        printf("This is an alphabet.\n");
     else if (c >= '0' && c <= '9') 
        printf("This is a digit.\n");
     else 
        printf("This is a special character.\n");
    return 0;
}

}
int main() 
{
    int c;
    while(1)
    {
        printf("Enter the question number: ");
        scanf("%d",&c);
        switch(c)
        {
            case 0:return 0;
            case 1:q1();break;
            case 2:q2();break;
            case 3:q3();break;
            case 4:q4();break;/*
            case 5:q5();break;
            case 6:q6();break;
            case 7:q7();break;
            case 9:q8();break;
            case 10:q9();break;
            case 11:q10();break;
            case 12:q12();break;
            case 13:q13();break;
            case 14:q14();break;
            case 15:q15();break;
            case 16:q16();break;
            case 17:q17();break;
            case 18:q1();break;
            case 19:q1();break;
            case 20:q1();break;
            case 21:q1();break;
            case 22:q1();break;
            case 23:q23();break;
            case 24:
            case 25:
            case 26:
            case 27:
            case 28:
            case 29:
            case 30:
            case 31:
            case 32:
            case 33:
            case 34:
            case 35:
            case 36:
            case 37:
            case 38:
            case 39:
            case 40:
            case 41:
            case 42:
            case 43:
            case 44:
            case 45:
            case 46:
            case 47:
            case 48:
            case 49:*/
            default:break;
        }
    }
}
