//delete capitals from a linked list containing characters

#include <stdio.h>
#include <stdlib.h>
// #define PRINTNICE(while(jj != NULL){};)

struct string
{
    char character;
    struct string *next;
};

struct string * newNode(char);
void printStr(struct string **);
void inputStr( struct string **);

int main()
{
    struct string **firstNode;
    printf("Enter the characters one by one and enter 0 to terminate:\n");
    inputStr(firstNode);
    printf("\nThe entered string is: ");
    printStr(firstNode);
}

struct string * newNode(char c)
{
    struct string * node = malloc(sizeof(struct string));
    node -> character = c;
    node -> next = NULL;
    return node;
}

void printStr(struct string ** head)
{
    struct string *ii;
    for (ii = *head; ii != NULL; ii = ii->next)
        printf("%c ==> ", ii->character);
}

void inputStr( struct string ** head )
{
    struct string *ii = *head;
    char ch;

    printf("-> ");
    printf("dummy");
    getchar();
    scanf("%c", &ch);
    // getchar();
    
    if(*head == NULL)
    {
        *head = newNode(ch);
        ii = *head;
        printf("inside if");
    }
    else
    {
        while ( ii -> character != '0' )
        {
            printStr(head);
            scanf("%c", &ch);
            ii = newNode(ch);
        }
    }
}