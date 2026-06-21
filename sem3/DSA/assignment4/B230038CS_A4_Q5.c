// B230038CS - Q5 - A4


#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int key;
    struct node* next;
} Item;

Item* createNode(int k) {
    Item* newNode = malloc(sizeof(Item));
    if (newNode == NULL) {
        printf("Memory allocation failed!\n");
        return NULL;
    }
    newNode->key = k;
    newNode->next = NULL;
    return newNode;
}

Item* createList(Item* head, int n) {
    Item* newNode, *currentNode;
    int k;
    for (int i = 0; i < n; i++) {
        printf("Enter a key: ");
        scanf("%d", &k);
        newNode = createNode(k);
        if (head == NULL) {
            currentNode = newNode;
            head = currentNode;
        } else {
            currentNode->next = newNode;
            currentNode = currentNode->next;
        }
    }
    return head;
}

void print(Item* head) {
    Item* current = head;
    if (current == NULL) {
        printf("Empty List\n");
        return;
    }
    printf("Linked List: ");
    while (current != NULL) {
        printf("-> %d ", current->key);
        current = current->next;
    }
    printf("\n");
}

Item* search(Item* head, int k) {
    while (head != NULL) {
        if (head->key == k) return head;
        head = head->next;
    }
    return NULL;
}

int count(Item* head) {
    int count = 0;
    while (head != NULL) {
        count++;
        head = head->next;
    }
    return count;
}

void addAtHead(Item** head, Item* node) {
    node->next = *head;
    *head = node;
}

void addAtTail(Item* head, Item* node) {
    if (head == NULL) {
        head = node;
        return;
    }
    Item* temp = head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = node;
}

void insert(Item* head, Item* node, int p) {
    if (p == 1) {
        node->next = head;
        head = node;
        return;
    }
    Item* temp = head;
    for (int i = 1; i < p - 1 && temp != NULL; i++) {
        temp = temp->next;
    }
    if (temp == NULL) {
        printf("Position out of range\n");
        return;
    }
    node->next = temp->next;
    temp->next = node;
}

void deleteByPosition(Item** head, int p) {
    if (*head == NULL) {
        printf("List is empty.\n");
        return;
    }
    Item* temp = *head;
    if (p == 1) {
        *head = temp->next;
        free(temp);
        return;
    }
    Item* prev = NULL;
    for (int i = 1; i < p && temp != NULL; i++) {
        prev = temp;
        temp = temp->next;
    }
    if (temp == NULL) {
        printf("Position out of range\n");
        return;
    }
    prev->next = temp->next;
    free(temp);
}

void deleteByValue(Item** head, int k) {
    Item* temp = *head;
    Item* prev = NULL;
    while (temp != NULL && temp->key == k) {
        *head = temp->next;
        free(temp);
        temp = *head;
    }
    while (temp != NULL) {
        while (temp != NULL && temp->key != k) {
            prev = temp;
            temp = temp->next;
        }
        if (temp == NULL) return;
        prev->next = temp->next;
        free(temp);
        temp = prev->next;
    }
}

Item* maximum(Item* head) {
    if (head == NULL) return NULL;
    Item* maxNode = head;
    while (head != NULL) {
        if (head->key > maxNode->key) maxNode = head;
        head = head->next;
    }
    return maxNode;
}

Item* minimum(Item* head) {
    if (head == NULL) return NULL;
    Item* minNode = head;
    while (head != NULL) {
        if (head->key < minNode->key) minNode = head;
        head = head->next;
    }
    return minNode;
}

void empty(Item** head) {
    Item* current = *head;
    Item* nextNode;
    while (current != NULL) {
        nextNode = current->next;
        free(current);
        current = nextNode;
    }
    *head = NULL;
}

int main() {
    Item* head = NULL;
    int choice, n, k, p;
    Item* node;

    printf("Enter the number of nodes: ");
    scanf("%d", &n);
    head = createList(head, n);
    print(head);

    do {
        printf("\nMenu:\n");
        printf("1. Search\n2. Count\n3. Add at Head\n4. Add at Tail\n");
        printf("5. Insert at Position\n6. Delete by Position\n");
        printf("7. Delete by Value\n8. Maximum\n9. Minimum\n");
        printf("10. Empty List\n11. Print List\n0. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
        case 0:
            printf("Exiting...\n");
            break;
        case 1:
            printf("Enter value to search: ");
            scanf("%d", &k);
            node = search(head, k);
            if (node != NULL) printf("Value found: %d\n", node->key);
            else printf("Value not found\n");
            break;
        case 2:
            printf("Number of nodes: %d\n", count(head));
            break;
        case 3:
            printf("Enter key to add at head: ");
            scanf("%d", &k);
            node = createNode(k);
            addAtHead(&head, node);
            print(head);
            break;
        case 4:
            printf("Enter key to add at tail: ");
            scanf("%d", &k);
            node = createNode(k);
            addAtTail(head, node);
            print(head);
            break;
        case 5:
            printf("Enter key and position: ");
            scanf("%d%d", &k, &p);
            node = createNode(k);
            insert(head, node, p);
            print(head);
            break;
        case 6:
            printf("Enter position to delete: ");
            scanf("%d", &p);
            deleteByPosition(&head, p);
            print(head);
            break;
        case 7:
            printf("Enter value to delete: ");
            scanf("%d", &k);
            deleteByValue(&head, k);
            print(head);
            break;
        case 8:
            node = maximum(head);
            if (node != NULL) printf("Maximum value: %d\n", node->key);
            else printf("List is empty.\n");
            break;
        case 9:
            node = minimum(head);
            if (node != NULL) printf("Minimum value: %d\n", node->key);
            else printf("List is empty.\n");
            break;
        case 10:
            empty(&head);
            printf("List emptied.\n");
            break;
        case 11:
            print(head);
            break;
        default:
            printf("Invalid choice.\n");
        }
    } while (choice != 0);

    empty(&head);
    return 0;
}
