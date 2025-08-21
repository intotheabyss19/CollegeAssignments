#include <stdio.h>
#include <stdlib.h>

#define MAX 100

// Function declarations
void initializeDeque(int deque[], int *front, int *rear, int k);
void addAtFront(int deque[], int *front, int *rear, int element);
void addAtRear(int deque[], int *front, int *rear, int element);
void deleteFromFront(int deque[], int *front, int *rear);
void deleteFromRear(int deque[], int *front, int *rear);
void display(int deque[], int *front, int *rear);
int isFull(int *front, int *rear);
int isEmpty(int *front, int *rear);

int main() {
    int deque[MAX];
    int front = -1, rear = -1;
    int choice, element, k;

    printf("Enter initial number of elements (k): ");
    scanf("%d", &k);
    
    initializeDeque(deque, &front, &rear, k);

    do {
        printf("\n\n---- DEQUE OPERATIONS ----\n");
        printf("1. Add at Front\n");
        printf("2. Add at Rear\n");
        printf("3. Delete from Front\n");
        printf("4. Delete from Rear\n");
        printf("5. Display\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                printf("Enter element to add at front: ");
                scanf("%d", &element);
                addAtFront(deque, &front, &rear, element);
                break;

            case 2:
                printf("Enter element to add at rear: ");
                scanf("%d", &element);
                addAtRear(deque, &front, &rear, element);
                break;

            case 3:
                deleteFromFront(deque, &front, &rear);
                break;

            case 4:
                deleteFromRear(deque, &front, &rear);
                break;

            case 5:
                display(deque, &front, &rear);
                break;

            case 6:
                printf("Exiting program...\n");
                break;

            default:
                printf("Invalid choice! Please try again.\n");
        }
    } while(choice != 6);

    return 0;
}

void initializeDeque(int deque[], int *front, int *rear, int k) {
    if(k > MAX) {
        printf("Initial size exceeds maximum capacity!\n");
        exit(1);
    }
    
    *front = 0;
    *rear = k - 1;
    
    printf("Enter %d elements:\n", k);
    for(int i = 0; i < k; i++) {
        scanf("%d", &deque[i]);
    }
}

int isFull(int *front, int *rear) {
    return (*front == 0 && *rear == MAX-1) || (*front == *rear + 1);
}

int isEmpty(int *front, int *rear) {
    return *front == -1;
}

void addAtFront(int deque[], int *front, int *rear, int element) {
    if(isFull(front, rear)) {
        printf("Overflow! Cannot add element.\n");
        return;
    }

    if(*front == -1) {
        *front = 0;
        *rear = 0;
    }
    else if(*front == 0) {
        *front = MAX - 1;
    }
    else {
        (*front)--;
    }
    
    deque[*front] = element;
    printf("Added %d at front\n", element);
}

void addAtRear(int deque[], int *front, int *rear, int element) {
    if(isFull(front, rear)) {
        printf("Overflow! Cannot add element.\n");
        return;
    }

    if(*front == -1) {
        *front = 0;
        *rear = 0;
    }
    else if(*rear == MAX-1) {
        *rear = 0;
    }
    else {
        (*rear)++;
    }
    
    deque[*rear] = element;
    printf("Added %d at rear\n", element);
}

void deleteFromFront(int deque[], int *front, int *rear) {
    if(isEmpty(front, rear)) {
        printf("Underflow! Deque is empty.\n");
        return;
    }

    printf("Deleted element: %d\n", deque[*front]);

    if(*front == *rear) {
        *front = -1;
        *rear = -1;
    }
    else if(*front == MAX-1) {
        *front = 0;
    }
    else {
        (*front)++;
    }
}

void deleteFromRear(int deque[], int *front, int *rear) {
    if(isEmpty(front, rear)) {
        printf("Underflow! Deque is empty.\n");
        return;
    }

    printf("Deleted element: %d\n", deque[*rear]);

    if(*front == *rear) {
        *front = -1;
        *rear = -1;
    }
    else if(*rear == 0) {
        *rear = MAX-1;
    }
    else {
        (*rear)--;
    }
}

void display(int deque[], int *front, int *rear) {
    if(isEmpty(front, rear)) {
        printf("Deque is empty!\n");
        return;
    }

    printf("Deque elements: ");
    if(*rear >= *front) {
        for(int i = *front; i <= *rear; i++) {
            printf("%d ", deque[i]);
        }
    }
    else {
        for(int i = *front; i < MAX; i++) {
            printf("%d ", deque[i]);
        }
        for(int i = 0; i <= *rear; i++) {
            printf("%d ", deque[i]);
        }
    }
    printf("\n");
}
