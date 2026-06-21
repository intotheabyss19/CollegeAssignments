// B230038CS - Q7 - A5

#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int key;
    struct Node *left, *right;
} Node;

Node* createBST(int list[], int n);
Node* insert(Node* root, int key);
Node* search(Node* root, int key);
Node* deleteNode(Node* root, int key);
Node* treeMinimum(Node* root);
Node* treeMaximum(Node* root);
void deleteTree(Node* root);
int getHeight(Node* root);
int getNodeCount(Node* root);
int getLeafCount(Node* root);
void inorder(Node* root);
void preorder(Node* root);
void postorder(Node* root);
void printLeaves(Node* root);
void printInternalNodes(Node* root);
void menu();

int main() {
    Node* root = NULL;
    int choice, key, n, *list;

    do {
        menu();
        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter the number of elements: ");
                scanf("%d", &n);
                list = (int*)malloc(n * sizeof(int));
                printf("Enter the elements: ");
                for (int i = 0; i < n; i++) scanf("%d", &list[i]);
                root = createBST(list, n);
                free(list);
                break;

            case 2:
                deleteTree(root);
                root = NULL;
                printf("Tree deleted.\n");
                break;

            case 3:
                printf("Enter key to insert: ");
                scanf("%d", &key);
                root = insert(root, key);
                break;

            case 4:
                printf("Enter key to search: ");
                scanf("%d", &key);
                printf(search(root, key) ? "Key found.\n" : "Key not found.\n");
                break;

            case 5:
                printf("Enter key to delete: ");
                scanf("%d", &key);
                root = deleteNode(root, key);
                break;

            case 6:
                if (root) printf("Minimum: %d\n", treeMinimum(root)->key);
                else printf("Tree is empty.\n");
                break;

            case 7:
                if (root) printf("Maximum: %d\n", treeMaximum(root)->key);
                else printf("Tree is empty.\n");
                break;

            case 8:
                printf("Height of tree: %d\n", getHeight(root));
                break;

            case 9:
                printf("Number of nodes: %d\n", getNodeCount(root));
                break;

            case 10:
                printf("Number of leaves: %d\n", getLeafCount(root));
                break;

            case 11:
                printf("Inorder traversal: ");
                inorder(root);
                printf("\n");
                break;

            case 12:
                printf("Preorder traversal: ");
                preorder(root);
                printf("\n");
                break;

            case 13:
                printf("Postorder traversal: ");
                postorder(root);
                printf("\n");
                break;

            case 14:
                printf("Leaves: ");
                printLeaves(root);
                printf("\n");
                break;

            case 15:
                printf("Internal nodes: ");
                printInternalNodes(root);
                printf("\n");
                break;

            case 16:
                printf("Exiting program.\n");
                break;

            default:
                printf("Invalid choice.\n");
        }
    } while (choice != 16);

    deleteTree(root);
    return 0;
}

void menu() {
    printf("\n---- Binary Search Tree Menu ----");
    printf("\n1. Create binary search tree");
    printf("\n2. Delete tree");
    printf("\n3. Insert a node");
    printf("\n4. Search a key");
    printf("\n5. Delete a node");
    printf("\n6. Tree Minimum");
    printf("\n7. Tree Maximum");
    printf("\n8. Get height");
    printf("\n9. Count nodes");
    printf("\n10. Count leaves");
    printf("\n11. Display in inorder");
    printf("\n12. Display in preorder");
    printf("\n13. Display in postorder");
    printf("\n14. Display leaves");
    printf("\n15. Display internal nodes");
    printf("\n16. Quit");
}

Node* createBST(int list[], int n) {
    Node* root = NULL;
    for (int i = 0; i < n; i++) root = insert(root, list[i]);
    return root;
}

Node* insert(Node* root, int key) {
    if (root == NULL) {
        Node* newNode = malloc(sizeof(Node));
	newNode->key = key;
        newNode->left = newNode->right = NULL;
        return newNode;
    }
    if (key < root->key) root->left = insert(root->left, key);
    else root->right = insert(root->right, key);
    return root;
}

Node* search(Node* root, int key) {
    if (root == NULL || root->key == key) return root;
    if (key < root->key) return search(root->left, key);
    return search(root->right, key);
}

Node* treeMinimum(Node* root) {
    while (root->left != NULL) root = root->left;
    return root;
}

Node* treeMaximum(Node* root) {
    while (root->right != NULL) root = root->right;
    return root;
}

Node* deleteNode(Node* root, int key) {
    if (root == NULL) return root;
    if (key < root->key) root->left = deleteNode(root->left, key);
    else if (key > root->key) root->right = deleteNode(root->right, key);
    else {
        if (root->left == NULL) {
            Node* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            Node* temp = root->left;
            free(root);
            return temp;
        }
        Node* temp = treeMinimum(root->right);
        root->key = temp->key;
        root->right = deleteNode(root->right, temp->key);
    }
    return root;
}

void deleteTree(Node* root) {
    if (root == NULL) return;
    deleteTree(root->left);
    deleteTree(root->right);
    free(root);
}

int getHeight(Node* root) {
    if (root == NULL) return -1;
    int leftHeight = getHeight(root->left);
    int rightHeight = getHeight(root->right);
    return 1 + (leftHeight > rightHeight ? leftHeight : rightHeight);
}

int getNodeCount(Node* root) {
    if (root == NULL) return 0;
    return 1 + getNodeCount(root->left) + getNodeCount(root->right);
}

int getLeafCount(Node* root) {
    if (root == NULL) return 0;
    if (root->left == NULL && root->right == NULL) return 1;
    return getLeafCount(root->left) + getLeafCount(root->right);
}

void inorder(Node* root) {
    if (root == NULL) return;
    inorder(root->left);
    printf("%d ", root->key);
    inorder(root->right);
}

void preorder(Node* root) {
    if (root == NULL) return;
    printf("%d ", root->key);
    preorder(root->left);
    preorder(root->right);
}

void postorder(Node* root) {
    if (root == NULL) return;
    postorder(root->left);
    postorder(root->right);
    printf("%d ", root->key);
}

void printLeaves(Node* root) {
    if (root == NULL) return;
    if (root->left == NULL && root->right == NULL) {
        printf("%d ", root->key);
        return;
    }
    printLeaves(root->left);
    printLeaves(root->right);
}

void printInternalNodes(Node* root) {
    if (root == NULL || (root->left == NULL && root->right == NULL)) return;
    printf("%d ", root->key);
    printInternalNodes(root->left);
    printInternalNodes(root->right);
}
