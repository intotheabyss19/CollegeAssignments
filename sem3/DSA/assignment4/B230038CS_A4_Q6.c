#include <stdio.h>
#include <stdlib.h>

// Definition of a stack node
struct Node {
    int data;
    struct Node* next;
};

// Definition of the stack structure
struct Stack {
    struct Node* top;
    int maxSize;
    int currentSize;
};

// Function to create a new stack
struct Stack* createStack(int max) {
    struct Stack* stack = (struct Stack*)malloc(sizeof(struct Stack));
    stack->top = NULL;
    stack->maxSize = max;
    stack->currentSize = 0;
    return stack;
}

// Function to check if the stack is empty
int isEmpty(struct Stack* stack) {
    return stack->currentSize == 0;
}

// Function to check if the stack is full
int isFull(struct Stack* stack) {
    return stack->currentSize == stack->maxSize;
}

// Function to push an element onto the stack
void push(struct Stack* stack, int x) {
    if (isFull(stack)) {
        printf("Stack Overflow! Cannot push %d\n", x);
        return;
    }
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = x;
    newNode->next = stack->top;
    stack->top = newNode;
    stack->currentSize++;
    printf("Pushed %d onto the stack.\n", x);
}

// Function to pop an element from the stack
int pop(struct Stack* stack) {
    if (isEmpty(stack)) {
        printf("Stack Underflow! Cannot pop from an empty stack.\n");
        return -1; // Return -1 to indicate underflow
    }
    struct Node* temp = stack->top;
    int poppedValue = temp->data;
    stack->top = stack->top->next;
    free(temp);
    stack->currentSize--;
    return poppedValue;
}

// Function to display the stack elements
void display(struct Stack* stack) {
    if (isEmpty(stack)) {
        printf("Stack is empty.\n");
        return;
    }
    struct Node* current = stack->top;
    printf("Stack elements (top to bottom):\n");
    while (current != NULL) {
        printf("%d\n", current->data);
        current = current->next;
    }
}

// Main function
int main() {
    int k, max, element;
    printf("Enter the initial number of elements (k): ");
    scanf("%d", &k);
    printf("Enter the maximum size of the stack: ");
    scanf("%d", &max);

    struct Stack* stack = createStack(max);

    // Initialize the stack with k elements
    printf("Enter %d elements to initialize the stack:\n", k);
    for (int i = 0; i < k; i++) {
        scanf("%d", &element);
        push(stack, element);
    }

    int choice;
    do {
        printf("\nMenu:\n");
        printf("1. Push\n");
        printf("2. Pop\n");
        printf("3. Display\n");
        printf("4. Quit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter the element to push: ");
                scanf("%d", &element);
                push(stack, element);
                break;
            case 2: {
                int poppedValue = pop(stack);
                if (poppedValue != -1) {
                    printf("Popped %d from the stack.\n", poppedValue);
                }
                break;
            }
            case 3:
                display(stack);
                break;
            case 4:
                printf("Quitting...\n");
                break;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    } while (choice != 4);

    // Free the stack memory
    while (!isEmpty(stack)) {
        pop(stack);
    }
    free(stack);

    return 0;
}
