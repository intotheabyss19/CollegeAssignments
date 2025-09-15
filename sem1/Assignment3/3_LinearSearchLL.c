/*
3. Write a program to search for a given value in a linked list by linear search with a function called
search_list. search_list will take two parameters: i) a pointer to the first node of a linked list L, and
ii) a value k. search_list will then return a pointer to the node of L containing k if k is present in L,
otherwise will return NULL if k is not present in L. Take L and k as input from the user, and print your final
output with an appropriate message.
*/

#include <stdio.h>
#include <stdlib.h>

// Definition of a node in the singly linked list
struct node {
    int key;
    struct node *next;
};

// Function to perform Linear Search over the linked list
struct node* Linear_search(struct node *node, int key)
{
    while(node != NULL)
    {
        if(node -> key == key)
            return node;
        node = node -> next;
    }
    return NULL;
}

// Function to create a new node
struct node *create_node(int key) 
{
    struct node *newnode = malloc(sizeof(struct node));
    newnode->key = key;
    newnode->next = NULL;
    return newnode;
}



int main() 
{
    int value, key;
    printf("Enter the elements of the linked list separated by spaces (enter -1 to terminate): ");
    
    struct node *head=NULL, *current, *node;
    
    while (1) 
	{
		scanf("%d", &value);
		if(value == -1)
			break;
		
        struct node *newnode = create_node(value);
        if (head == NULL) 
		{
            head = newnode;
            current = head;
        }
		else 
		{
            current->next = newnode;
            current = current->next;
        }
    }

    printf("Enter the key:");
    scanf("%d", &key);

    node = Linear_search(head, key);
    
    if(node == NULL)
        printf("The given element was not found\n");
    else
        printf("The given element is present in the linked list\n");

    return 0;
}

//Done