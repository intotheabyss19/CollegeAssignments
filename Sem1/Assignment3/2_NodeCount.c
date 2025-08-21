/*
Write a function called get_Node_count to count the number of Nodes in a singly linked list.
get_Node_count will take only one parameter which is a pointer to the first Node of a linked list L, and will
return the number of Nodes in L. Take a linked list L as input from the user, call get_Node_count from your
main function with the first Node of L as the argument, and then print the number of Nodes in L as the final
output of your program.
*/

#include <stdio.h>
#include <stdlib.h>

// Definition of a Node in the singly linked list
struct Node 
{
    int data;
    struct Node *next;
};

// Function to get the count of the Nodes
int get_Node_count(struct Node *head) 
{
    int count = 0;
    struct Node *current = head;
    
    while (current != NULL) 
    {
        count++;
        current = current->next;
    }
    
    return count;
}

// Function to create a new Node
struct Node *create_node(int key) 
{
    struct Node *newNode = malloc(sizeof(struct Node));
    newNode->data = key;
    newNode->next = NULL;
    return newNode;
}



int main() 
{
    int value, count;
    printf("Enter the elements of the linked list separated by spaces (enter -1 to terminate): ");
    
    struct Node *head=NULL, *current;
    
    while (1) 
	{
		scanf("%d", &value);
		if(value == -1)
			break;
		
        struct Node *newNode = create_node(value);
        if (head == NULL) 
		{
            head = newNode;
            current = head;
        }
		else 
		{
            current->next = newNode;
            current = current->next;
        }
    }
    printf("Number of Nodes in the linked list: %d\n", get_Node_count(head));
    return 0;
}

//Done