/*
 * 7.Write a program to create the game of Tower of Hanoi. The game consists of three stacks, say s1, s2, s3,
where every stack has its elements arranged in a non-decreasing order from top to bottom, i.e. in any stack
s, a push operation can be performed only if the element x to be pushed to s is less than to equal to the top
element t of s (i.e. if x > t, then push is not allowed in s). Initially, s1 has n elements, and s2 and s3 are
empty. The objective of the game is to transfer all the n elements from s1 to s3 by a series of moves where
a move is defined as popping an element x from a stack si and then pushing x to another stack sj (where,
1 ≤ i ≤ 3, 1 ≤ j ≤ 3, and i ≠ j). Note that only one move can be made at a time. Your program will initially
take the value of n and the elements of s1 as input from the user, and then will repeatedly display the
contents s1, s2, and s3, along with a menu where the user is given the option to make a move. Each time
the menu is displayed, the user will choose the source stack for the pop operation and destination stack for
the push operation for one single move. The menu and the stack contents will be displayed repeatedly until
the game is solved or the user chooses to quit. If the game is solved, your program will print the number of
moves taken by the user to solve the game. Take the elements of the stack to be of int type, and do not use
any external variable.
*/

#include <stdio.h>
#include <stdlib.h>

#define MAXSTACKSIZE 20

void insertInOrder(int s[], int n, int key) {
    int i = n - 1;
    while (i >= 0 && s[i] > key) {
        s[i + 1] = s[i];
        i--;
    }
    s[i + 1] = key;
}

int top(int s[], int n) {
    int i = 0;
    while (s[i] != 0)
        i++;
    return i==0 ? i : i-1;
}

int isSorted(int s[], int n) {
    for (int i = 1; i < n; i++)
        if (s[i - 1] > s[i])
            return 0;
    return 1;
}

int isFull(int s[], int n) {
    return top(s, n) == n - 1;
}

int isEmpty(int s[], int n) {
    return s[top(s, n)] == 0;
}

int push(int s[], int key, int *n) {
    if (isFull(s, *n))
        return -1;
    s[++(*n)] = key;
    return 1;

    (*n)++;
    return 1;
}

int pop(int s[], int *n) {
    if (*n == 0)
        return -1;
    int index = top(s, *n);
    int temp = s[index];
    s[index] = 0;
    (*n)--;
    return temp;
}

void levelCreator(int s[], int *n) {
    printf("\n\t...Create your instance of the game...\n");
    printf("\t--------------------------------------\n");
    do
    {
        printf("Enter the number of game pieces (MAXSIZE is 20): ");
        scanf("%d", n);
    } while (*n > 20);
    printf("\nConstruct the tower...\n\nEnter the elements:\n");
    int key;
    for (int i = 0; i < *n; i++) {
        printf("\t>>> ");
        scanf("%d", &key);
        insertInOrder(s, i, key);
    }
    printf("\nLevel Created Successfully.....\n");
    printf("Press Enter to Continue.");
    getchar(); getchar();
}

void showTowers(int *s[], int n) {
    int i, j;
    system("clear");
    printf("\n\t...Game Screen...\n");
    printf("\t-----------------\n");
    for (i = 0; i < n; i++) {
        for (j = 0; j < 3; j++) {
            if (s[j][i] <= 0)
                printf("\t -");
            else
                printf("\t %d", s[j][i]);
        }
        printf("\n");
    }
    printf("\t<S1>\t<S2>\t<S3>\n");
}

int move(int *s[], int *n, int move) {
    int push_selector, pop_selector, temp;
    printf("Move is: %d\n", move);

    push_selector = move % 10;
    pop_selector = move / 10;

    printf("Entering move loop\n");
    printf("push selector is %d and pop selector is %d\n", push_selector, pop_selector);

    if (push_selector > 3 || push_selector < 1 || pop_selector > 3 || pop_selector < 1) 
    {
        printf("Error: Invalid Move\n");
        return -1;
    }

    if (!isEmpty(s[pop_selector - 1], *n)) {
        if (isEmpty(s[push_selector - 1], *n) || s[pop_selector - 1][top(s[pop_selector - 1], *n)] <= s[push_selector - 1][top(s[push_selector - 1], *n)]) {
            temp = pop(s[pop_selector - 1], n);
            push(s[push_selector - 1], temp, n);
            return 1;
        } else {
            printf("Error: Invalid Move\n");
            return -1;
        }
    } else {
        printf("Error: Invalid Move\n");
        return -1;
    }
}

int checkWin(int s[], int *n)
{
    if (isFull(s, *n) == -1){
        printf("line 122\n");
        return 1;
    }
    else return -1;
}


int main() {
    int n = 3, mv, s1[100] = {0}, s2[100] = {0}, s3[100] = {0};
    int *s[3] = {s1, s2, s3};
    int count = 0;
    system("clear");
    levelCreator(s[0], &n);

    showTowers(s, n);

    do
    {
        do
        {
            printf("Enter your move (2 Digit Integer: Source Tower * 10 + Destination Tower) ==> ");
            scanf("%d", &mv);
        } while(mv/100 != 0 && mv%10 != mv); // checking if mv is a 2 digit number

        if (move (s, &n, mv) == 1) {
            count++;
        }
    } while (checkWin(s[3], &n) != 1);

    printf("Game Completed\n");
    showTowers(s, n);
    printf("Number of moves: %d\n", count);
    return 0;
}
