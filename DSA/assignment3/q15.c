/*
15. Write a program to implement multiple stacks with a single array. Your program will store k stacks, taking
k as input from the user, in an array A of maximum size max, where k * n = max for some positive integer
n. The k stacks will be initially stored by dividing A into k equal segments, each of size n, with the ith
segment representing the ith stack, where i = 1 to k. Therefore, in the initial arrangment, the bottom of the
1st stack will be stored in the 0 th index of A, the bottom of the 2nd stack will be stored in the (0+n.1)th index
of A, the bottom of the 3rd stack will be stored in the (0+n.2)th index of A, and so on. Your program will
create a menu-based interface where the user can choose to perform push and pop operations on any of the
k stacks. The program should be able to perform push operations in a stack as long as there is free space
available in A, implying that stacks may need to be shifted from their initial arrangement to accommodate a
new element for a particular stack as long as there is free space available in A to make the shift operation
possible (refer to the method of checking for free space in an array representing multiple stacks given in
the textbook by Horowitz et al.). A stack will be considered empty if the index of its top element is less
than the index of its bottom element. Your program will repeatedly display the menu until the user chooses
to quit.
*/

#include <stdio.h>
#include <stdlib.h>

#define MAX 100

typedef struct {
    int *arr;
    int *top;
    int *base;
    int k, n, max;
} Stack;

Stack* createStack(int k, int n) {
    Stack* s = (Stack*)malloc(sizeof(Stack));
    s->k = k;
    s->n = n;
    s->max = k * n;
    s->arr = (int*)malloc(s->max * sizeof(int));
    s->top = (int*)malloc(s->k * sizeof(int));
    s->base = (int*)malloc(s->k * sizeof(int));

    for (int i = 0; i < s->k; i++) {
        s->top[i] = -1;
        s->base[i] = i * n;
    }
    return s;
}

int isFull(Stack* s) {
    for (int i = 0; i < s->k; i++) {
        if (s->top[i] < s->base[i] + s->n - 1) {
            return 0;
        }
    }
    return 1;
}

int isEmpty(Stack* s, int sn) {
    return s->top[sn] < s->base[sn];
}

void push(Stack* s, int sn, int x) {
    if (isFull(s)) {
        printf("Stack is full. Cannot push %d into stack %d\n", x, sn);
        return;
    }

    if (s->top[sn] == s->base[sn] + s->n - 1) {
        for (int i = s->k - 1; i > sn; i--) {
            for (int j = s->base[i]; j < s->base[i] + s->n; j++) {
                s->arr[j + 1] = s->arr[j];
            }
            s->top[i]++;
            s->base[i]++;
        }
    }

    s->arr[++s->top[sn]] = x;
}

int pop(Stack* s, int sn) {
    if (isEmpty(s, sn)) {
        printf("Stack %d is empty. Cannot pop\n", sn);
        return -1;
    }

    return s->arr[s->top[sn]--];
}

void display(Stack* s) {
    for (int i = 0; i < s->k; i++) {
        printf("Stack %d: ", i);
        for (int j = s->base[i]; j <= s->top[i]; j++) {
            printf("%d ", s->arr[j]);
        }
        printf("\n");
    }
}

int main() {
    int k, n;
    printf("Enter the number of stacks: ");
    scanf("%d", &k);
    printf("Enter the size of each stack: ");
    scanf("%d", &n);

    Stack* s = createStack(k, n);

    while (1) {
        printf("1. Push\n");
        printf("2. Pop\n");
        printf("3. Display\n");
        printf("4. Quit\n");
        int choice;
        scanf("%d", &choice);

        switch (choice) {
            case 1: {
                int sn, x;
                printf("Enter the stack number: ");
                scanf("%d", &sn);
                printf("Enter the element to push: ");
                scanf("%d", &x);
                push(s, sn, x);
                break;
            }
            case 2: {
                int sn;
                printf("Enter the stack number: ");
                scanf("%d", &sn);
                printf("Popped element: %d\n", pop(s, sn));
                break;
            }
            case 3:
                display(s);
                break;
            case 4:
                return 0;
            default:
                printf("Invalid choice\n");
        }
    }

    return 0;
}