// B230038CS - Q20 - A4

#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int key;
    struct Node* prev;
    struct Node* next;
} Node;

typedef struct Stack {
    Node* top;
} Stack;

Node* createNode(int key) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) {
        printf("Memory allocation failed!\n");
        return NULL;
    }
    newNode->key = key;
    newNode->prev = NULL;
    newNode->next = NULL;
    return newNode;
}

void initStack(Stack* stack) {
    stack->top = NULL;
}

void push(Stack* stack, int key) {
    Node* newNode = createNode(key);
    if (!newNode) return;
    newNode->next = stack->top;
    if (stack->top != NULL) {
        stack->top->prev = newNode;
    }
    stack->top = newNode;
}

int pop(Stack* stack) {
    if (stack->top == NULL) {
        printf("Stack underflow!\n");
        return -1;
    }
    Node* temp = stack->top;
    int key = temp->key;
    stack->top = stack->top->next;
    if (stack->top != NULL) {
        stack->top->prev = NULL;
    }
    free(temp);
    return key;
}

void printStack(Stack* stack) {
    Node* current = stack->top;
    while (current != NULL) {
        printf("%d ", current->key);
        current = current->next;
    }
    printf("\n");
}

int isMoveLegal(Stack* src, Stack* dest) {
    if (src->top == NULL) {
        return 0;
    }
    if (dest->top == NULL || src->top->key < dest->top->key) {
        return 1;
    }
    return 0;
}

int main() {
    Stack s1, s2, s3;
    int n, disk, source, destination;
    int moves = 0;

    initStack(&s1);
    initStack(&s2);
    initStack(&s3);

    printf("Enter the number of disks: ");
    scanf("%d", &n);
    for (int i = n; i >= 1; i--) {
        push(&s1, i);
    }

    while (s3.top != NULL || s1.top != NULL || s2.top != NULL) {
        printf("\nCurrent State:\n");
        printf("Stack 1: ");
        printStack(&s1);
        printf("Stack 2: ");
        printStack(&s2);
        printf("Stack 3: ");
        printStack(&s3);

        printf("\nChoose a move:\n");
        printf("Source Stack (1-3): ");
        scanf("%d", &source);
        printf("Destination Stack (1-3): ");
        scanf("%d", &destination);

        if (source == destination) {
            printf("Source and destination cannot be the same. Try again.\n");
            continue;
        }

        Stack* src = NULL;
        Stack* dest = NULL;
        int disk;

        if (source == 1) src = &s1;
        else if (source == 2) src = &s2;
        else if (source == 3) src = &s3;

        if (destination == 1) dest = &s1;
        else if (destination == 2) dest = &s2;
        else if (destination == 3) dest = &s3;

        if (isMoveLegal(src, dest)) {
            disk = pop(src);
            push(dest, disk);
            moves++;
            printf("Moved disk %d from Stack %d to Stack %d\n", disk, source, destination);
        } else {
            printf("Illegal move. Try again.\n");
        }

        if (s3.top != NULL && s3.top->next == NULL && s3.top->key == n) {
            printf("\nGame solved in %d moves!\n", moves);
            break;
        }
    }

    return 0;
}
