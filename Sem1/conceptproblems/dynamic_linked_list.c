#include <stdio.h>
#include <stdlib.h>

struct Node
{
    char ASCII_Val;
    struct Node *nextNode;
};
int main()
{
    int i, NumOfNodes;
    char val;
    struct Node *ii, *firstnode, *tempnode;
    
    printf("Enter the number of entries: ");
    scanf("%d", &NumOfNodes);

    for(i = 0; i<NumOfNodes; i++)
    {   
        tempnode = malloc (sizeof(struct Node));
        printf("Enter an ASCII Character: ");
        scanf("%c", &val);
        tempnode -> ASCII_Val = val;
        tempnode -> nextNode = NULL;
        for(ii=firstnode; ii->nextNode == NULL; ii=ii->nextNode);
        ii = tempnode;

        printf("The given node has been successfully added to the linked list.\n");
    }

    printf("\nPrinting the values of the linked list ==>\n");
    //Printing the values of the linked list
    for(ii=firstnode; ii->nextNode = NULL; ii=ii->nextNode);
        printf("%c --> ", ii-> ASCII_Val);
    printf("\nAll Nodes have been printed successfully\n");

    return 0;
}