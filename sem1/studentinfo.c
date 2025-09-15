#include <stdio.h>

struct studentinfo
{
    char name[100];
    char roll[10];
    float cgpa;
};

//function to input information of the student
struct studentinfo student()
{
    // char name[100], roll[10];
    // float cgpa;
    struct studentinfo st;
    printf("Enter your name: ");
    scanf("%s", st.name);
    // fgets(s.name, 100, stdin);
    printf("Enter your roll number: ");
    scanf("%s", st.roll);
    // fgets(s.roll, 100, stdin);
    printf("CGPA obtained: ");
    scanf("%f", &st.cgpa);
    return st;
}

//function to print the elements of the given structure properly
void display(struct studentinfo s)
{
    printf("\nName of the student: %s", s.name);
    printf("\n");
    printf("Roll number: ");
    fputs(s.roll, stdout);
    printf("\n");
    printf("CGPA obtained: %f", s.cgpa);
    printf("\n");
    return;
}
    
int main()
{
    struct studentinfo s1 = student();
    display(s1);
    return 0;
}