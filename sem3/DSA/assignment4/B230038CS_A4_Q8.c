// B230038CS - Q8 - A4

#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* prev;
    struct Node* next;
} Node;

typedef struct Queue {
    Node* front;
    Node* rear;
    int size;
    int maxSize;
} Queue;

Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) {
        printf("Memory allocation failed!\n");
        return NULL;
    }
    newNode->data = data;
    newNode->prev = NULL;
    newNode->next = NULL;
    return newNode;
}

Queue* createQueue(int maxSize) {
    Queue* q = (Queue*)malloc(sizeof(Queue));
    if (!q) {
        printf("Memory allocation failed!\n");
        return NULL;
    }
    q->front = NULL;
    q->rear = NULL;
    q->size = 0;
    q->maxSize = maxSize;
    return q;
}

int isEmpty(Queue* q) {
    return q->size == 0;
}

int isFull(Queue* q) {
    return q->size == q->maxSize;
}

void add(Queue* q, int data) {
    if (isFull(q)) {
        printf("Queue overflow! Cannot add element.\n");
        return;
    }
    Node* newNode = createNode(data);
    if (!newNode) return;

    if (q->rear == NULL) {
        q->front = q->rear = newNode;
    } else {
        q->rear->next = newNode;
        newNode->prev = q->rear;
        q->rear = newNode;
    }
    q->size++;
    printf("Added %d to the queue.\n", data);
}

int delete(Queue* q) {
    if (isEmpty(q)) {
        printf("Queue underflow! Cannot delete element.\n");
        return -1;
    }
    Node* temp = q->front;
    int data = temp->data;

    if (q->front == q->rear) {
        q->front = q->rear = NULL;
    } else {
        q->front = q->front->next;
        q->front->prev = NULL;
    }
    free(temp);
    q->size--;
    printf("Deleted %d from the queue.\n", data);
    return data;
}

void display(Queue* q) {
    if (isEmpty(q)) {
        printf("Queue is empty.\n");
        return;
    }
    Node* temp = q->front;
    printf("Queue (front -> rear): ");
    while (temp) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

int main() {
    int maxSize, k, choice, data;

    printf("Enter the maximum size of the queue: ");
    scanf("%d", &maxSize);

    Queue* q = createQueue(maxSize);

    printf("Enter the number of initial elements (<= %d): ", maxSize);
    scanf("%d", &k);

    if (k > maxSize) {
        printf("Error: Number of initial elements exceeds maximum size.\n");
        return 1;
    }

    printf("Enter the elements of the queue:\n");
    for (int i = 0; i < k; i++) {
        scanf("%d", &data);
        add(q, data);
    }

    do {
        printf("\nChoose an option:\n");
        printf("1. Add\n");
        printf("2. Delete\n");
        printf("3. Display\n");
        printf("4. Quit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            printf("Enter the element to add: ");
            scanf("%d", &data);
            add(q, data);
            break;

        case 2:
            delete(q);
            break;

        case 3:
            display(q);
            break;

        case 4:
            printf("Exiting...\n");
            break;

        default:
            printf("Invalid choice! Please try again.\n");
        }
    } while (choice != 4);

    while (!isEmpty(q)) {
        delete(q);
    }
    free(q);

    return 0;
}

